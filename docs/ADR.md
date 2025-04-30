# Architecture Decision Records (ADR)

This document captures the key architectural and technology decisions made for the ImageLibrary project. Each record follows the pattern:

- **Context**: Background and driving forces behind the decision.
- **Decision**: The chosen solution or approach.
- **Consequences**: Benefits and potential drawbacks.

---

## ADR 001: Python Runtime Version

### Context
- DCC tools in the VFX pipeline (e.g., Maya 2023) embed Python 3.9.x.
- We want local development and container environments to be consistent.

### Decision
Use **Python 3.11** as the project’s runtime.

### Consequences
- **Positive**: Access to latest language features, improved performance, and security fixes.
- **Negative**: Some third-party libraries (e.g., older PySide versions) may require compatibility testing or workarounds.

---

## ADR 002: Web Framework Selection

### Context
- The project requires a lightweight RESTful API, template rendering, and simple routing.
- Full-stack frameworks (e.g., Django) may add unnecessary complexity.

### Decision
Adopt **Flask** as the web framework.

### Consequences
- **Positive**: Minimal overhead, flexible, easy to integrate with existing code and extensions.
- **Negative**: Manual wiring for components like authentication or admin panels; additional work for larger-scale features.

---

## ADR 003: Database Engine

### Context
- Development and testing benefit from zero-configuration databases.
- Production environments may require more robust, networked systems.

### Decision
Use **SQLite** by default, with the option to switch to **MySQL/PostgreSQL** via configuration.

### Consequences
- **Positive**: Fast setup, no external dependencies for dev/test; easy file-based backups.
- **Negative**: Limited concurrency and scalability; will need migration scripts (Flask-Migrate) when switching engines.

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
- **Negative**: Added complexity for CI/CD pipelines; slight performance overhead.

---

## ADR 005: Front-End Framework

### Context
- Need responsive, mobile-friendly UI for image galleries and forms.
- Avoid heavy front-end frameworks if unnecessary for MVP.

### Decision
Use **Bootstrap 5** for styling and layout.

### Consequences
- **Positive**: Rapid UI development, consistent components, responsive grid by default.
- **Negative**: Limited interactivity out of the box; may need custom JavaScript for advanced UX.

---

## ADR 006: Testing & CI Tools

### Context
- Maintain code quality and prevent regressions.
- Automate test execution and coverage reporting.

### Decision
- Use **pytest** for unit tests.
- Use **pytest-cov** for coverage reports.
- Integrate **GitHub Actions** for CI and **Codecov** for coverage visualization.

### Consequences
- **Positive**: Automated feedback on code health, clear coverage metrics, early detection of errors.
- **Negative**: CI configuration overhead; reliance on external services (Codecov).


