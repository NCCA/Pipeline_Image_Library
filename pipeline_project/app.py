from flask import Flask, request, render_template, redirect, url_for
import os
import sqlite3
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'static/uploads'

# Initialising the database
def init_db():
    with sqlite3.connect('database.db') as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS images (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                filename TEXT NOT NULL,
                tags TEXT
            )
        ''')

@app.route('/', methods=['GET', 'POST'])
def index():
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    if request.method == 'POST':
        file = request.files['image']
        tags = request.form.get('tags', '')
        if file:
            filename = secure_filename(file.filename)
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(filepath)

            cursor.execute('INSERT INTO images (filename, tags) VALUES (?, ?)', (filename, tags))
            conn.commit()
            return redirect(url_for('index'))

    q = request.args.get('q')
    if q:
        cursor.execute('SELECT filename, tags FROM images WHERE tags LIKE ?', (f'%{q}%',))
    else:
        cursor.execute('SELECT filename, tags FROM images')

    images = cursor.fetchall()
    conn.close()
    return render_template('index.html', images=images)

if __name__ == '__main__':
    os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
    init_db()
    app.run(debug=True, port=5001)

