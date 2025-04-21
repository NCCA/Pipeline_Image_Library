import os
import sqlite3
from flask import Flask, request, render_template, redirect, url_for, g
from werkzeug.utils import secure_filename

def create_app(test_config=None):
    # 1) Create the Flask application instance
    app = Flask(__name__, instance_relative_config=True)

    # 2) Default configuration: place the database file in the instance folder
    app.config.from_mapping(
        SECRET_KEY='dev',
        DATABASE=os.path.join(app.instance_path, 'database.db'),
        UPLOAD_FOLDER=os.path.join(app.root_path, 'static', 'uploads'),
    )

    # 3) Override default configuration with test_config if provided
    if test_config is not None:
        app.config.update(test_config)

    # 4) Ensure the instance folder and upload folder exist
    try:
        os.makedirs(app.instance_path, exist_ok=True)
        os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
    except OSError:
        pass

    # 5) Database connection helper, stored in flask.g
    def get_db():
        if 'db' not in g:
            g.db = sqlite3.connect(
                app.config['DATABASE'],
                detect_types=sqlite3.PARSE_DECLTYPES
            )
            g.db.row_factory = sqlite3.Row
        return g.db

    @app.teardown_appcontext
    def close_db(error):
        db = g.pop('db', None)
        if db is not None:
            db.close()

    # 6) Initialize the database by creating the images table if it doesn't exist
    def init_db():
        db = get_db()
        db.executescript('''
            CREATE TABLE IF NOT EXISTS images (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                filename TEXT NOT NULL,
                tags TEXT,
                uploaded_at DATETIME DEFAULT CURRENT_TIMESTAMP
            );
        ''')

    # Register a Flask CLI command 'init-db' to initialize the database
    import click
    @app.cli.command('init-db')
    def init_db_command():
        """Initialize the database."""
        init_db()
        click.echo('Initialized the database.')

    # 7) Routes: upload, search, and display images
    @app.route('/', methods=['GET', 'POST'])
    def index():
        db = get_db()

        if request.method == 'POST':
            file = request.files['image']
            tags = request.form.get('tags', '')
            if file:
                filename = secure_filename(file.filename)
                filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
                file.save(filepath)
                db.execute(
                    'INSERT INTO images (filename, tags) VALUES (?, ?)',
                    (filename, tags)
                )
                db.commit()
            return redirect(url_for('index'))

        q = request.args.get('q', '')
        if q:
            images = db.execute(
                'SELECT filename, tags FROM images WHERE tags LIKE ?',
                (f'%{q}%',)
            ).fetchall()
        else:
            images = db.execute('SELECT filename, tags FROM images').fetchall()

        return render_template('index.html', images=images)

    return app


# 8) Entry point: create the app and run the development server
if __name__ == '__main__':
    app = create_app()
    app.run(debug=True)
