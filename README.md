# ImageLibrary

[![Coverage Status](https://img.shields.io/badge/coverage-67%25-yellow)](https://github.com/NCCA/pipeline-project-Flora9822/actions)


**ImageLibrary** is a web-based 2D image reference database inspired by PureRef. It allows users to upload, tag, search, and organize images into custom moodboards.

## Features

- Upload images with tags for quick categorization.
- Search and filter images by keywords.
- Create and manage multiple moodboards, adding or removing images as needed.
- Responsive gallery view for easy browsing and preview.
- Containerized deployment via Docker or Podman.

## Tech Stack

- **Backend:** Flask (Python) with SQLite (default) or MySQL
- **Frontend:** HTML, CSS, Bootstrap (extendable to React/Vue)
- **Testing:** pytest
- **Deployment:** Docker + docker-compose (or Podman)

## Quick Start

### Prerequisites

- Python 3.11
- Git
- Docker or Podman

### Installation

1. **Clone the repository:**
   ```bash
   git clone git@github.com:NCCA/pipeline-project-Flora9822.git
   cd pipeline_project
   ```

2. **Set up the Python environment and install dependencies:**
   ```bash
   python -m venv venv
   source venv/bin/activate    # Windows: venv\\Scripts\\activate
   pip install -r requirements.txt
   ```

3. **Initialize the database:**
   ```bash
   export FLASK_APP=app.py
   flask init-db
   ```

4. **Run the application:**
   ```bash
   python app.py
   ```
   Open your browser and go to `http://127.0.0.1:5000`

## Usage

- **Home page:** Upload images and search by tags.
- **Moodboards:** Use the navigation link to view, create, and manage custom moodboards.

## Testing

Run automated tests with pytest:
```bash
pytest -q
```

## Docker Deployment

Below is an example of a `Dockerfile` and `docker-compose.yml` to build and launch the application with one command.

### Dockerfile

```dockerfile
# Use official Python 3.11 slim image
FROM python:3.11-slim

# Set working directory
WORKDIR /app

# Copy requirements and install dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy project files
COPY . .

# Expose Flask port
EXPOSE 5000

# Start the application
CMD ["python", "app.py"]
```

### docker-compose.yml

```yaml
version: '3.8'

services:
  web:
    build: .
    ports:
      - "5000:5000"
    volumes:
      # Mount uploads folder for persistent storage
      - ./static/uploads:/app/static/uploads
    environment:
      - FLASK_APP=app.py
      - FLASK_ENV=production
```

### Quick Launch

From the project root:

```bash
docker-compose up -d --build
```

Open your browser to:

```
http://localhost:5000
```

Or with Podman:

```bash
podman-compose up -d --build
```

## Contribution

1. Create a feature branch:
   ```bash
git checkout -b feature/your-feature
```
2. Commit your changes:
   ```bash
git commit -m "Add new feature"
```
3. Push and open a Pull Request:
   ```bash
git push origin feature/your-feature
```

## License

This project is licensed under the MIT License.

