import os
import tempfile
import pytest
from app import create_app

@pytest.fixture
def app():
    # 1) Create a temporary database file
    db_fd, db_path = tempfile.mkstemp()

    # 2) Test configuration: override the DATABASE path
    test_config = {
        'TESTING': True,
        'DATABASE': db_path,
    }

    # 3) Instantiate the application using the factory
    app = create_app(test_config)

    # 4) Initialize the database tables via the CLI command
    runner = app.test_cli_runner()
    runner.invoke(args=['init-db'])

    yield app

    # 5) Clean up the temporary database file
    os.close(db_fd)
    os.unlink(db_path)

@pytest.fixture
def client(app):
    return app.test_client()

@pytest.fixture
def runner(app):
    return app.test_cli_runner()
