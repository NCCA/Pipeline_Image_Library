# API Documentation

This document describes the ImageLibrary application's HTTP endpoints, their methods, parameters, and example usage.

---

## 1. Home (Image Gallery)

**Endpoint:** `/`

**Methods:**
- `GET` — List all images (optionally filtered and sorted)
- `POST` — Upload a new image

### Query Parameters (GET)
- `q` (string, optional): keyword filter on tags. Example: `/` or `/?q=city`
- `sort` (string, optional): sort order. Valid values:
  - `date_desc` (default)
  - `date_asc`
  - `name_asc`
  - `name_desc`

### Form Data (POST)
- `image` (file, required): image file (`png`, `jpg`, `jpeg`, `gif`)
- `tags` (string, optional): comma-separated labels. Example: `cyberpunk, city`

### Responses
- **GET** returns 200 HTML page with image grid.
- **POST** on success redirects (302) back to `/`.
- On validation error, flashes message and redirects back.

### Examples
```bash
curl "http://localhost:5000/?q=sky&sort=name_asc"
```
```bash
curl -X POST -F "image=@path/to/pic.png" -F "tags=sky,cloud" http://localhost:5000/
```

---

## 2. Delete Image

**Endpoint:** `/delete/<image_id>`

**Methods:**
- `POST` — Delete image record and file

### URL Parameters
- `<image_id>` (int, required): ID of the image to delete.

### Responses
- On success: 302 redirect to `/`.
- If image not found: still redirects to `/`.

### Example
```bash
curl -X POST http://localhost:5000/delete/5
```

---

## 3. Moodboards

### 3.1 List Moodboards

**Endpoint:** `/moodboards`

**Methods:**
- `GET` — Show all moodboards

### Response
- 200 HTML list of boards with name and description.

---

## 3.2 Create Moodboard

**Endpoint:** `/moodboards/create`

**Methods:**
- `GET` — Show form to create a new moodboard
- `POST` — Submit new moodboard

### Form Data (POST)
- `name` (string, required): moodboard name
- `description` (string, optional): brief description

### Responses
- On success: 302 redirect to `/moodboards`
- On form error: flash message, redirect back

### Example
```bash
curl -X POST -d "name=MyBoard" -d "description=Inspiration" http://localhost:5000/moodboards/create
```

---

## 3.3 Moodboard Detail and Image Assignment

**Endpoint:** `/moodboards/<mid>`

**Methods:**
- `GET` — Display moodboard detail with assigned images
- `POST` — Add an existing image to the moodboard

### URL Parameters
- `<mid>` (int, required): moodboard ID

### Form Data (POST)
- `image_id` (int, required): ID of image to add

### Responses
- On success: 302 redirect to the same detail page
- On duplicate: uses `INSERT OR IGNORE`, no duplicate entries

### Example
```bash
curl -X POST -d "image_id=3" http://localhost:5000/moodboards/1
```

---

