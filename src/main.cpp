#include "World.h"
#include "RigidBody.h"
#include "Renderer.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/Mat4.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "RigidBody Dynamics", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialise NGL
    ngl::NGLInit::initialize();

    // Initialise shaders
    ngl::ShaderLib::createShaderProgram("nglDiffuseShader");
    ngl::ShaderLib::attachShader("DiffuseVertex", ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader("DiffuseFragment", ngl::ShaderType::FRAGMENT);
    ngl::ShaderLib::loadShaderSource("DiffuseVertex", "/home/s5722414/Documents/RigidBodyDynamics/shaders/vertex_shader.glsl");
    ngl::ShaderLib::loadShaderSource("DiffuseFragment", "/home/s5722414/Documents/RigidBodyDynamics/shaders/fragment_shader.glsl");
    ngl::ShaderLib::compileShader("DiffuseVertex");
    ngl::ShaderLib::compileShader("DiffuseFragment");
    ngl::ShaderLib::attachShaderToProgram("nglDiffuseShader", "DiffuseVertex");
    ngl::ShaderLib::attachShaderToProgram("nglDiffuseShader", "DiffuseFragment");
    ngl::ShaderLib::linkProgramObject("nglDiffuseShader");
    ngl::ShaderLib::use("nglDiffuseShader");

    ngl::ShaderLib::setUniform("lightPosition", 0.0f, 10.0f, 10.0f);
    ngl::ShaderLib::setUniform("lightColor", 1.0f, 1.0f, 1.0f);

    // Initialisation depth test
    glEnable(GL_DEPTH_TEST);

    // Create the world and renderer
    World world;
    Renderer renderer;

    // Setting up the projection and view matrices
    ngl::Mat4 projectionMatrix = ngl::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    ngl::Mat4 viewMatrix = ngl::lookAt({0.0f, 5.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    renderer.setProjectionMatrix(projectionMatrix);
    renderer.setViewMatrix(viewMatrix);

    // Add a rigid body
    auto body1 = std::make_unique<RigidBody>();
    body1->position = glm::vec3(-1.0f, 0.0f, 0.0f);
    body1->velocity = glm::vec3(1.0f, 0.0f, 0.0f);
    world.addRigidBody(std::move(body1));

    auto body2 = std::make_unique<RigidBody>();
    body2->position = glm::vec3(1.0f, 0.0f, 0.0f);
    body2->velocity = glm::vec3(-1.0f, 0.0f, 0.0f);
    world.addRigidBody(std::move(body2));

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        world.simulate(0.016f); // Update the world
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.render(world.getBodies()); // Render the rigid body
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleaning up resources
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
