import io
import pytest
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
    with app.app_context():
        app.test_cli_runner().invoke(args=['init-db'])
    uploads.mkdir(exist_ok=True)
    return app.test_client()

def test_delete_image(client, tmp_path):
    uploads = tmp_path / "uploads"
    data = {
        'image': (io.BytesIO(b"fake-image-data"), 'to_delete.png'),
        'tags': 'test'
    }
    client.post('/', data=data, content_type='multipart/form-data')
    assert (uploads / 'to_delete.png').exists()

    # Delete the image
    response = client.post('/delete/1', follow_redirects=True)
    assert response.status_code == 200

    # The filename should no longer appear in the page HTML
    assert b'to_delete.png' not in client.get('/').data

    # The file should also be removed from the upload folder
    assert not (uploads / 'to_delete.png').exists()
