#include "Renderer.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>
#include <iostream>

Renderer::Renderer() {
    std::cout << "Initializing Renderer..." << std::endl;


    ngl::VAOPrimitives::createSphere("sphere", 1.0f, 32); // Create the sphere
}

Renderer::~Renderer() {
    std::cout << "Destroying Renderer..." << std::endl;
}

void Renderer::setViewMatrix(const ngl::Mat4 &viewMatrix) {
    m_viewMatrix = viewMatrix;
}

void Renderer::setProjectionMatrix(const ngl::Mat4 &projectionMatrix) {
    m_projectionMatrix = projectionMatrix;
}

void Renderer::render(const std::vector<std::unique_ptr<RigidBody>> &bodies) {
    ngl::ShaderLib::use("nglDiffuseShader");

    for (const auto &body : bodies) {
         // Construct the transformation matrix
        ngl::Transformation transform;
        transform.setPosition(ngl::Vec3(body->position.x, body->position.y, body->position.z));
        transform.setRotation(body->rotationAxis.x * body->rotationAngle,
                              body->rotationAxis.y * body->rotationAngle,
                              body->rotationAxis.z * body->rotationAngle);

        // Calculate the MVP matrix
        ngl::Mat4 modelMatrix = transform.getMatrix();
        ngl::Mat4 MVP = m_projectionMatrix * m_viewMatrix * modelMatrix;

        // Setting uniform variables
        ngl::ShaderLib::setUniform("MVP", MVP);
        ngl::ShaderLib::setUniform("modelMatrix", modelMatrix);

        // Draw the sphere
        ngl::VAOPrimitives::draw("sphere");
    }
}
