import io
import os
import sqlite3

def test_init_db_command(runner, app):
    """Test that the init-db CLI command successfully creates the images table."""
    result = runner.invoke(args=['init-db'])
    assert 'Initialized the database.' in result.output

    # Verify that the table exists
    conn = sqlite3.connect(app.config['DATABASE'])
    cursor = conn.cursor()
    cursor.execute(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='images';"
    )
    assert cursor.fetchone() is not None
    conn.close()

def test_upload_and_display(client):
    """Test that after uploading an image, the homepage displays its filename and tags."""
    # Read the fixture image
    path = os.path.join(os.getcwd(), 'tests', 'fixtures', 'sample.png')
    with open(path, 'rb') as f:
        img_bytes = f.read()

    data = {
        'image': (io.BytesIO(img_bytes), 'sample.png'),
        'tags': 'test,pytest'
    }
    resp = client.post('/', data=data, content_type='multipart/form-data', follow_redirects=True)
    assert resp.status_code == 200
    assert b'sample.png' in resp.data
    assert b'test,pytest' in resp.data

def test_search_functionality(client):
    """Test that the search endpoint returns only images matching the search query."""
    # Upload two images with different tags: apple and banana
    for name, tag in [('a.png', 'apple'), ('b.png', 'banana')]:
        with open(os.path.join('tests/fixtures/sample.png'), 'rb') as f:
            img = f.read()
        client.post(
            '/',
            data={'image': (io.BytesIO(img), name), 'tags': tag},
            content_type='multipart/form-data'
        )

    # Search for 'apple'
    resp = client.get('/?q=apple')
    assert b'a.png' in resp.data
    assert b'b.png' not in resp.data
