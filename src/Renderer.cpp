#include "Renderer.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include <random>

Renderer::Renderer() {
    // Initialize OpenGL rendering settings
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
    glEnable(GL_COLOR_MATERIAL);  // Enable color material to set colors for primitives
    glShadeModel(GL_SMOOTH);  // Enable smooth shading
}

Renderer::~Renderer() {}

//------------------------------------------------------------------
// Draw Sphere in Immediate Mode (for visualization)
//------------------------------------------------------------------
static void drawSphereImmediateMode(const glm::vec3 &center, float radius, const glm::vec3 &color) {
    const int slices = 16;  // Number of slices (latitude divisions)
    const int stacks = 16;  // Number of stacks (longitude divisions)

    // Loop through the stacks to create the sphere
    for (int i = 0; i < stacks; ++i) {
        float lat0 = 3.14159f * (-0.5f + (float)i / stacks);
        float z0 = sin(lat0);  // Z-coordinate of the sphere
        float zr0 = cos(lat0);  // Radius at the current latitude

        float lat1 = 3.14159f * (-0.5f + (float)(i + 1) / stacks);
        float z1 = sin(lat1);  // Z-coordinate of the next latitude
        float zr1 = cos(lat1);  // Radius at the next latitude

        glBegin(GL_QUAD_STRIP);  // Start drawing a strip of quads
        for (int j = 0; j <= slices; j++) {
            float lng = 2.f * 3.14159f * (float)j / slices;
            float x = cos(lng);  // X-coordinate of the sphere
            float y = sin(lng);  // Y-coordinate of the sphere

            // First vertex at the current latitude
            float nx = x * zr0;
            float ny = y * zr0;
            float nz = z0;

            glColor3f(color.r, color.g, color.b);  // Use the specified color
            glVertex3f(center.x + radius * nx, center.y + radius * ny, center.z + radius * nz);

            // Second vertex at the next latitude
            nx = x * zr1;
            ny = y * zr1;
            nz = z1;
            glVertex3f(center.x + radius * nx, center.y + radius * ny, center.z + radius * nz);
        }
        glEnd();
    }
}

//------------------------------------------------------------------
// Draw Plane in Immediate Mode (for ground visualization)
//------------------------------------------------------------------
static void drawPlaneImmediateMode(float groundY, float halfSize) {
    glColor3f(0.6f, 0.6f, 0.6f);  // Set the color to gray for the ground
    glBegin(GL_QUADS);  // Draw a quadrilateral for the ground
    glVertex3f(-halfSize, groundY, -halfSize);
    glVertex3f(halfSize, groundY, -halfSize);
    glVertex3f(halfSize, groundY, halfSize);
    glVertex3f(-halfSize, groundY, halfSize);
    glEnd();
}

//------------------------------------------------------------------
// Render the bodies (no contact line rendering)
//------------------------------------------------------------------
void Renderer::render(const std::vector<std::unique_ptr<RigidBody>> &bodies,
                      const glm::mat4 &view,
                      const glm::mat4 &projection) {
    glMatrixMode(GL_PROJECTION);  // Set projection matrix mode
    glLoadIdentity();  // Load the identity matrix to clear any previous transformations
    glMultMatrixf(glm::value_ptr(projection));  // Apply the projection matrix

    glMatrixMode(GL_MODELVIEW);  // Set modelview matrix mode
    glLoadIdentity();  // Load identity matrix to clear transformations
    glMultMatrixf(glm::value_ptr(view));  // Apply the view matrix

    // Render each rigid body (draw the sphere)
    for (auto &body : bodies) {
        drawSphereImmediateMode(body->position, body->radius, body->color);  // Pass the color to draw the sphere
    }
}

//------------------------------------------------------------------
// Generate a random color for visualizing rigid bodies
//------------------------------------------------------------------
glm::vec3 generateRandomColor() {
    static std::random_device rd;  // Initialize random number generator
    static std::mt19937 gen(rd());  // Mersenne Twister engine
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);  // Uniform distribution for RGB values

    return glm::vec3(dis(gen), dis(gen), dis(gen));  // Return a random RGB color
}

//------------------------------------------------------------------
// Render the ground (flat plane) for the world
//------------------------------------------------------------------
void Renderer::renderGround(float groundY, float halfSize,
                            const glm::mat4 &view,
                            const glm::mat4 &projection) {
    glMatrixMode(GL_PROJECTION);  // Set projection matrix mode
    glLoadIdentity();  // Clear previous transformations
    glMultMatrixf(glm::value_ptr(projection));  // Apply the projection matrix

    glMatrixMode(GL_MODELVIEW);  // Set modelview matrix mode
    glLoadIdentity();  // Clear transformations
    glMultMatrixf(glm::value_ptr(view));  // Apply the view matrix

    // Draw the ground plane
    drawPlaneImmediateMode(groundY, halfSize);
}
