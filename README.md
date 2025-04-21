Project Title
2D Image Reference Database

Technical Approach and Architecture

1.Frontend:
User Interface:
Build a responsive web interface that allows users to upload images, enter descriptions, and specify keywords. Display the images in a grid or list format.
Search and Sorting:
Implement functionality to search images by keywords and sort them by criteria such as upload time or tags.
Extended Features:
If time allows, add additional features like drag-and-drop layout adjustments and custom mood board creation.

2.Backend:
Server Framework:
Use a lightweight web framework like Python Flask to set up a RESTful API for handling image uploads, storage, queries, and management.
Database:
Use SQLite as the database to store image metadata such as file paths, descriptions, keywords, and upload timestamps. Design a simple schema to categorize images based on moods or themes.
File Storage:
Store image files on the server’s local directory, with associated metadata recorded in the database.
Containerization and Deployment:

3.Docker/Podman Deployment:
Create a Dockerfile and a Docker Compose configuration file to containerize the frontend, backend, and database components. This ensures consistent deployment across different environments.
Local Storage Mounting:
Configure the container to mount a local directory for persistent image data storage, ensuring data remains available even if the container is restarted.