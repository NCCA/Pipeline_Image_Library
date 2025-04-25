import io
import pytest
from app import create_app

@pytest.fixture
def client(tmp_path):
   
    db_path = tmp_path / "test.db"
    app = create_app({'TESTING': True, 'DATABASE': str(db_path)})
    with app.app_context():
        app.test_cli_runner().invoke(args=['init-db'])
    return app.test_client()

def test_upload_no_file(client):
    """When submitting a POST without a file, it should flash an error and return status 200."""
    response = client.post(
        '/',
        data={'tags': 'no file'},
        content_type='multipart/form-data',
        follow_redirects=True
    )
    assert response.status_code == 200
   
    assert b'No file part' in response.data or b'No selected file' in response.data

def test_upload_invalid_file_type(client):
    """When uploading a non-image file, it should flash 'Invalid file type'."""
    fake_txt = io.BytesIO(b"not an image")
    data = {
        'image': (fake_txt, 'test.txt'),
        'tags': 'invalid'
    }
    response = client.post(
        '/',
        data=data,
        content_type='multipart/form-data',
        follow_redirects=True
    )
    assert response.status_code == 200
    assert b'Invalid file type' in response.data
