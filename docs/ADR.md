# Architecture Decision Records (ADR)

This document captures the key architectural and technology decisions made for the ImageLibrary project. Each record follows the pattern:

- **Context**: Background and driving forces behind the decision.  
- **Decision**: The chosen solution or approach.  
- **Consequences**: Benefits and potential drawbacks.

---

## Table of Contents

- [ADR 001: Python Runtime Version](#adr-001-python-runtime-version)  
- [ADR 002: Web Framework Selection](#adr-002-web-framework-selection)  
- [ADR 003: Database Engine](#adr-003-database-engine)  
- [ADR 004: Containerization Strategy](#adr-004-containerization-strategy)  
- [ADR 005: Front-End Framework](#adr-005-front-end-framework)  
- [ADR 006: Testing & CI Tools](#adr-006-testing--ci-tools)  
- [ADR 007: Bulk Upload Feature](#adr-007-bulk-upload-feature)  
- [ADR 008: Pagination Strategy](#adr-008-pagination-strategy)  

---

## ADR 001: Python Runtime Version

### Context
- DCC tools in the VFX pipeline (e.g., Maya 2023) embed Python 3.9.x.  
- We want local development and container environments to be consistent.

### Decision
Use **Python 3.11** as the project’s runtime.

### Consequences
- **Positive**: Latest language features, better performance, security updates.  
- **Negative**: Some third-party or DCC-specific libraries may require compatibility testing.

---

## ADR 002: Web Framework Selection

### Context
- The project requires a lightweight RESTful API, template rendering, and simple routing.  
- Full-stack frameworks (e.g., Django) add unnecessary complexity.

### Decision
Adopt **Flask** as the web framework.

### Consequences
- **Positive**: Minimal boilerplate, highly flexible, easy to integrate small extensions.  
- **Negative**: Manual wiring for features like authentication and admin panels.

---

## ADR 003: Database Engine

### Context
- Development and testing benefit from zero-configuration databases.  
- Production environments may require a more robust, networked database.

### Decision
Use **SQLite** by default, with the option to switch to **MySQL** or **PostgreSQL** via configuration.

### Consequences
- **Positive**: Instant setup, file-based backups, no external dependencies for dev/test.  
- **Negative**: Limited concurrency and scalability; migration scripts needed for other engines.

---

## ADR 004: Containerization Strategy

### Context
- Ensure consistent environments across developers and deployment targets.  
- Simplify onboarding and infrastructure management.

### Decision
- Containerize the application using **Docker** (and support **Podman**).  
- Base image: `python:3.11-slim`.  
- Orchestrate with **docker-compose.yml** for local development.

### Consequences
- **Positive**: Reproducible builds, environment parity, simplified dependency management.  
- **Negative**: Added CI/CD configuration overhead; slight runtime overhead.

---

## ADR 005: Front-End Framework

### Context
- Need a responsive, mobile-friendly UI for image galleries and forms.  
- Avoid heavy front-end frameworks if unnecessary for MVP.

### Decision
Use **Bootstrap 5** for styling and layout.

### Consequences
- **Positive**: Rapid UI development, consistent components, built-in responsive grid.  
- **Negative**: Limited rich interactivity; custom JavaScript required for advanced UX.

---

## ADR 006: Testing & CI Tools

### Context
- Maintain code quality and prevent regressions.  
- Automate test execution and coverage reporting.

### Decision
- Use **pytest** for unit and edge-case tests.  
- Use **pytest-cov** for coverage metrics.  
- Integrate **GitHub Actions** for CI and **Codecov** for coverage visualization.

### Consequences
- **Positive**: Automated feedback on code health, clear coverage dashboards, early detection of issues.  
- **Negative**: Additional CI/CD setup; dependency on external services.

---

## ADR 007: Bulk Upload Feature

### Context
- Users need to upload multiple reference images at once.  
- Provide visual feedback on upload progress.

### Decision
- Front-end `<input type="file" multiple>` support.  
- Use AJAX (`XMLHttpRequest.upload.onprogress`) to render a progress bar.  
- Back-end loops through `request.files`, saving and inserting each image record.

### Consequences
- **Positive**: Smooth multi-file upload experience and progress visibility.  
- **Negative**: More complex front-end JavaScript; need robust error handling for large uploads.

---

## ADR 008: Pagination Strategy

### Context
- With many images, loading all at once degrades performance and UX.  
- Need page-by-page navigation.

### Decision
- Back-end reads `?page=` parameter and applies `LIMIT`/`OFFSET` in SQL.  
- Front-end displays pagination controls (previous/next, page numbers).

### Consequences
- **Positive**: Reduced payload per page, faster initial load.  
- **Negative**: Additional requests when navigating pages; must ensure SEO-friendly links if public.

---
