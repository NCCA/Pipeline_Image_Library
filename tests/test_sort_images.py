import io
import pytest
from app import create_app

@pytest.fixture
def client(tmp_path):
    db_path = tmp_path / "test.db"
    app = create_app({
        'TESTING': True,
        'DATABASE': str(db_path)
    })
    with app.app_context():
        app.test_cli_runner().invoke(args=['init-db'])
    return app.test_client()

def upload_image(client, filename):
    """Helper to upload a dummy image with a fixed tag."""
    return client.post(
        '/',
        data={
            'image': (io.BytesIO(b"dummy-data"), filename),
            'tags': 'tag'
        },
        content_type='multipart/form-data',
        follow_redirects=True
    )

def test_sort_by_name_asc(client):
    upload_image(client, 'b_image.png')
    upload_image(client, 'a_image.png')
    response = client.get('/?sort=name_asc')
    # 'a_image.png' should appear before 'b_image.png'
    assert response.data.index(b'a_image.png') < response.data.index(b'b_image.png')

def test_sort_by_date_desc(client):
    upload_image(client, 'first.png')
    upload_image(client, 'second.png')
    response = client.get('/?sort=date_desc')
    # 'second.png' (newest) should appear before 'first.png'
    assert response.data.index(b'second.png') < response.data.index(b'first.png')

def test_sort_by_date_asc(client):
    upload_image(client, 'old.png')
    upload_image(client, 'new.png')
    response = client.get('/?sort=date_asc')
    # 'old.png' (oldest) should appear before 'new.png'
    assert response.data.index(b'old.png') < response.data.index(b'new.png')

