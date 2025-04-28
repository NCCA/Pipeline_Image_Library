
# ImageLibrary

[![Coverage Status](https://img.shields.io/badge/coverage-67%25-yellow)](https://github.com/NCCA/pipeline-project-Flora9822/actions)

**ImageLibrary** is a web-based 2D image reference database inspired by PureRef. It allows users to upload, tag, search, and organize images into custom moodboards.

## Features

- Upload images with tags for quick categorization.
- Search and filter images by keywords (case‑insensitive, partial matches).
- Create and manage multiple boards, adding or removing images.
- Responsive gallery view using Bootstrap.
- Test coverage and CI via pytest and GitHub Actions.
- Containerized deployment with Docker Compose.

## Tech Stack

- **Backend:** Flask (Python) with SQLite (default) or MySQL
- **Frontend:** HTML, CSS, Bootstrap
- **Testing:** pytest, pytest-cov
- **CI/CD:** GitHub Actions, Codecov
- **Deployment:** Docker, Docker Compose

## Quick Start

### Prerequisites

- Python 3.11
- Git
- Docker & Docker Compose (optional for container deployment)

### Installation

Clone the repository and install dependencies:
```bash
git clone git@github.com:NCCA/pipeline-project-Flora9822.git
cd pipeline_project
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install -r requirements.txt
```

## Deployment & Running

### 1. Docker Compose (one‑step)

If you have Docker and Docker Compose:
```bash
docker-compose up -d --build
```
- Builds the image with dependencies.
- Runs the Flask app on port 5000.
- Persists uploaded images via volume `./static/uploads`.

Open your browser at `http://localhost:5000`.

### 2. Local Setup Script (Linux/macOS)

Use the provided `setup.sh` to automate setup, migration, and startup:
```bash
chmod +x setup.sh
./setup.sh
```
This will:
1. Create and activate a Python virtual environment.
2. Install dependencies.
3. Initialize the database (`flask init-db`).
4. Start the development server (`flask run`).

Visit `http://127.0.0.1:5000` to access the app.

## Usage

- **Home:** Upload images and search by tags.
- **Boards:** Create new boards and add images via the navigation menu.

## Testing

Run unit tests and view coverage:
```bash
pytest --cov=app --cov-report=term-missing
```


## Architecture

For a detailed system overview, data flow, and ER diagrams, see [Architecture Documentation](docs/ARCHITECTURE.md).


## Contributing

1. Fork the repo and create a feature branch:
   ```bash
git checkout -b feature/your-feature
```
2. Commit your changes:
   ```bash
git commit -m "Add some feature"
```
3. Push to your fork and open a Pull Request.

## License

This project is licensed under the MIT License.

