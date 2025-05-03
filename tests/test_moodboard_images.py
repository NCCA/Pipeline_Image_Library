import io
import pytest
from app import create_app

@pytest.fixture
def client(tmp_path):
    # Set up temporary DB and upload folder
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


def upload_image(client, filename):
    """Helper: upload a dummy image with a tag."""
    return client.post(
        '/',
        data={
            'image': (io.BytesIO(b'data'), filename),
            'tags': 't'
        },
        content_type='multipart/form-data',
        follow_redirects=True
    )


def test_create_and_add_image_to_board(client):
    # Upload two images
    upload_image(client, 'img1.png')
    upload_image(client, 'img2.png')

    # Create a moodboard
    resp = client.post('/moodboards/create', data={
        'name': 'MyBoard',
        'description': 'Desc'
    }, follow_redirects=True)
    assert resp.status_code == 200
    assert b'MyBoard' in resp.data

    # Add img1 to the board
    resp = client.post('/moodboards/1', data={'image_id': '1'}, follow_redirects=True)
    assert resp.status_code == 200
    # Board detail shows img1.png
    assert b'img1.png' in resp.data
    # The dropdown for adding images should list img2.png as available
    assert b'img2.png' in resp.data

        # Attempt to add same image again, count remains unchanged
    initial_count = resp.data.count(b'img1.png')
    resp = client.post('/moodboards/1', data={'image_id': '1'}, follow_redirects=True)
    assert resp.data.count(b'img1.png') == initial_count
