
import io
import os
import pytest
from app import create_app

@pytest.fixture
def client(tmp_path):
    # Use a temporary file for the database
    db_path = tmp_path / "test.db"
    app = create_app({'TESTING': True, 'DATABASE': str(db_path)})
    with app.app_context():
        app.test_cli_runner().invoke(args=['init-db'])
    return app.test_client()

def upload_image(client, filename, tags):
    """Helper to upload the same sample.png under different names/tags."""
    img_path = os.path.join('tests', 'fixtures', 'sample.png')
    with open(img_path, 'rb') as f:
        img_bytes = f.read()
    data = {
        'image': (io.BytesIO(img_bytes), filename),
        'tags': tags
    }
    return client.post('/', data=data, content_type='multipart/form-data', follow_redirects=True)

def test_search_empty_returns_all(client):
    """Empty or missing query should return all images."""
    upload_image(client, 'one.png', 'apple')
    upload_image(client, 'two.png', 'banana')

    # Empty q parameter
    response1 = client.get('/?q=')
    assert b'one.png' in response1.data
    assert b'two.png' in response1.data

    # No q parameter at all
    response2 = client.get('/')
    assert b'one.png' in response2.data
    assert b'two.png' in response2.data

def test_search_case_insensitive(client):
    """Search should ignore case."""
    upload_image(client, 'A.png', 'CyberPunk')
    upload_image(client, 'B.png', 'cyberpunk')

    response_lower = client.get('/?q=cyberpunk')
    assert b'A.png' in response_lower.data
    assert b'B.png' in response_lower.data

    response_upper = client.get('/?q=CYBERPUNK')
    assert b'A.png' in response_upper.data
    assert b'B.png' in response_upper.data

def test_search_partial_match(client):
    """Partial matches should be returned."""
    upload_image(client, 'city.png', 'cityscape')
    upload_image(client, 'forest.png', 'forest')

    response = client.get('/?q=city')
    assert b'city.png' in response.data
    assert b'forest.png' not in response.data
