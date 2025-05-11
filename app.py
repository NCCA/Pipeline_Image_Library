import os
import sqlite3
import click
from flask import (
    Flask, request, render_template,
    redirect, url_for, g, flash
)
from werkzeug.utils import secure_filename

ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg', 'gif'}

def create_app(test_config=None):
    """Create and configure the Flask application."""
    app = Flask(__name__, instance_relative_config=True)
    app.config.from_mapping(
        SECRET_KEY='dev',
        DATABASE=os.path.join(app.instance_path, 'database.db'),
        UPLOAD_FOLDER=os.path.join(app.root_path, 'static', 'uploads'),
    )

    if test_config:
        app.config.update(test_config)

    os.makedirs(app.instance_path, exist_ok=True)
    os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)

    def get_db():
        """Open a database connection if there isn't one yet."""
        if 'db' not in g:
            g.db = sqlite3.connect(
                app.config['DATABASE'],
                detect_types=sqlite3.PARSE_DECLTYPES
            )
            g.db.row_factory = sqlite3.Row
        return g.db

    @app.teardown_appcontext
    def close_db(error=None):
        """Close the database again at the end of the request."""
        db = g.pop('db', None)
        if db:
            db.close()

    def init_db():
        """Initialize the database tables."""
        db = get_db()
        db.executescript('''
            CREATE TABLE IF NOT EXISTS images (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                filename TEXT NOT NULL,
                tags TEXT,
                uploaded_at DATETIME DEFAULT CURRENT_TIMESTAMP
            );
            CREATE TABLE IF NOT EXISTS moodboards (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                description TEXT
            );
            CREATE TABLE IF NOT EXISTS moodboard_images (
                moodboard_id INTEGER NOT NULL,
                image_id INTEGER NOT NULL,
                PRIMARY KEY (moodboard_id, image_id),
                FOREIGN KEY (moodboard_id) REFERENCES moodboards(id) ON DELETE CASCADE,
                FOREIGN KEY (image_id) REFERENCES images(id) ON DELETE CASCADE
            );
        ''')

    @app.cli.command('init-db')
    def init_db_command():
        """CLI command to initialize the database."""
        init_db()
        click.echo('Initialized the database.')

    def allowed_file(filename):
        """Check that the uploaded file has an allowed image extension."""
        return (
            '.' in filename and
            filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS
        )

    @app.route('/', methods=['GET', 'POST'])
    def index():
        db = get_db()

        if request.method == 'POST':
            tags = request.form.get('tags', '')

            # 1) Bulk upload first
            if 'images' in request.files:
                files = request.files.getlist('images')
                # No filenames at all?
                if not any(f.filename for f in files):
                    flash('No selected file')
                    return redirect(request.url)
                # Any invalid extension?
                for f in files:
                    if f and f.filename and not allowed_file(f.filename):
                        flash('Invalid file type')
                        return redirect(request.url)
                # save them
                for f in files:
                    fn = secure_filename(f.filename)
                    f.save(os.path.join(app.config['UPLOAD_FOLDER'], fn))
                    db.execute(
                        'INSERT INTO images (filename, tags) VALUES (?, ?)',
                        (fn, tags)
                    )
                db.commit()
                return redirect(url_for('index'))

            # 2) Fallback to single-file upload
            if 'image' not in request.files:
                flash('No file part')
                return redirect(request.url)
            file = request.files['image']
            if file.filename == '':
                flash('No selected file')
                return redirect(request.url)
            if not allowed_file(file.filename):
                flash('Invalid file type')
                return redirect(request.url)

            fn = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], fn))
            db.execute(
                'INSERT INTO images (filename, tags) VALUES (?, ?)',
                (fn, tags)
            )
            db.commit()
            return redirect(url_for('index'))

        # GET: pagination, search & sort
        page = max(1, int(request.args.get('page', 1)))
        per_page = 20
        offset = (page - 1) * per_page

        q = request.args.get('q', '')
        sort = request.args.get('sort', 'date_desc')

        base = 'SELECT id, filename, tags, uploaded_at FROM images'
        params = ()
        if q:
            base += ' WHERE tags LIKE ?'
            params = (f'%{q}%',)

        if sort == 'date_asc':
            order = 'ORDER BY uploaded_at ASC, id ASC'
        elif sort == 'date_desc':
            order = 'ORDER BY uploaded_at DESC, id DESC'
        elif sort == 'name_asc':
            order = 'ORDER BY LOWER(filename) ASC, id ASC'
        elif sort == 'name_desc':
            order = 'ORDER BY LOWER(filename) DESC, id DESC'
        else:
            order = 'ORDER BY uploaded_at DESC, id DESC'

        images = db.execute(
            f"{base} {order} LIMIT ? OFFSET ?",
            params + (per_page, offset)
        ).fetchall()
        total = db.execute(
            f"SELECT COUNT(*) FROM images" + (' WHERE tags LIKE ?' if q else ''),
            params
        ).fetchone()[0]
        total_pages = max(1, (total + per_page - 1) // per_page)

        return render_template(
            'index.html',
            images=images,
            page=page,
            total_pages=total_pages,
            q=q,
            sort=sort
        )

    @app.route('/delete/<int:image_id>', methods=['POST'])
    def delete_image(image_id):
        """Delete an image record and its file."""
        db = get_db()
        row = db.execute(
            'SELECT filename FROM images WHERE id = ?', (image_id,)
        ).fetchone()
        if row:
            fn = row['filename']
            db.execute('DELETE FROM images WHERE id = ?', (image_id,))
            db.commit()
            try:
                os.remove(os.path.join(app.config['UPLOAD_FOLDER'], fn))
            except OSError:
                pass
        return redirect(url_for('index'))

    @app.route('/moodboards')
    def list_moodboards():
        """Show all moodboards."""
        db = get_db()
        boards = db.execute(
            'SELECT id, name, description FROM moodboards'
        ).fetchall()
        return render_template('moodboards.html', moodboards=boards)

    @app.route('/moodboards/create', methods=['GET', 'POST'])
    def create_moodboard():
        """Create a new moodboard."""
        db = get_db()
        if request.method == 'POST':
            name = request.form['name']
            desc = request.form.get('description', '')
            cur = db.execute(
                'INSERT INTO moodboards (name, description) VALUES (?, ?)',
                (name, desc)
            )
            db.commit()
            return redirect(url_for('moodboard_detail', mid=cur.lastrowid))
        return render_template('create_moodboard.html')

    @app.route('/moodboards/<int:mid>', methods=['GET', 'POST'])
    def moodboard_detail(mid):
        """View and add images to a specific moodboard."""
        db = get_db()
        if request.method == 'POST':
            img_id = int(request.form['image_id'])
            db.execute(
                'INSERT OR IGNORE INTO moodboard_images (moodboard_id, image_id) '
                'VALUES (?, ?)', (mid, img_id)
            )
            db.commit()
            return redirect(url_for('moodboard_detail', mid=mid))

        mb = db.execute(
            'SELECT id, name, description FROM moodboards WHERE id = ?', (mid,)
        ).fetchone()
        all_imgs = db.execute('SELECT id, filename, tags FROM images').fetchall()
        mb_imgs = db.execute(
            'SELECT images.id, images.filename, images.tags '
            'FROM images JOIN moodboard_images '
            'ON images.id = moodboard_images.image_id '
            'WHERE moodboard_images.moodboard_id = ?',
            (mid,)
        ).fetchall()

        return render_template(
            'moodboard_detail.html',
            moodboard=mb,
            all_images=all_imgs,
            mb_images=mb_imgs
        )

    return app

if __name__ == '__main__':
    app = create_app()
    with app.app_context():
        try:
            app.cli.commands['init-db'].callback()
        except Exception:
            pass
    app.run(debug=True)
