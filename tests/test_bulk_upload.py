import io
import pytest
import sqlite3
from pathlib import Path
from app import create_app

@pytest.fixture
def client(tmp_path):
    db_path = tmp_path / "test.db"
    uploads = tmp_path / "uploads"
    app = create_app({
        'TESTING': True,
        'DATABASE': str(db_path),
        'UPLOAD_FOLDER': str(uploads)
    })

    # Initialize the database
    with app.app_context():
        app.test_cli_runner().invoke(args=['init-db'])

    uploads.mkdir(exist_ok=True)
    return app.test_client()

def test_bulk_upload_multiple_images(client, tmp_path):
    """
    Test uploading multiple images in one request under the 'images' field,
    then verify that the files exist on disk and records are in the database.
    """
    uploads = Path(client.application.config['UPLOAD_FOLDER'])

    # Send POST request with bulk images
    data = {
        'tags': 'bulk',
        'images': [
            (io.BytesIO(b"fake1"), 'one.png'),
            (io.BytesIO(b"fake2"), 'two.jpg'),
        ]
    }
    resp = client.post(
        '/',
        data=data,
        content_type='multipart/form-data',
        follow_redirects=True
    )
    assert resp.status_code == 200

    # The files should have been saved to disk
    assert (uploads / 'one.png').exists()
    assert (uploads / 'two.jpg').exists()

    # Verify database records
    db_file = client.application.config['DATABASE']
    conn = sqlite3.connect(db_file)
    cursor = conn.cursor()
    cursor.execute("SELECT filename, tags FROM images ORDER BY id")
    rows = cursor.fetchall()
    conn.close()

    assert rows == [
        ('one.png', 'bulk'),
        ('two.jpg', 'bulk'),
    ]
