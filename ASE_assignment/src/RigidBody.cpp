#include "RigidBody.h"
#include <iostream>

// Default constructor
RigidBody::RigidBody()
    : position(0.0f), velocity(0.0f), acceleration(0.0f), force(0.0f), mass(1.0f), radius(1.0f) {
    color = generateRandomColor();  // Generate random color for visualization
    updateInverseMass();  // Update inverse mass based on the mass
}

// Parameterized constructor
RigidBody::RigidBody(const glm::vec3 &pos)
    : position(pos), velocity(0.0f), acceleration(0.0f), force(0.0f), mass(1.0f), radius(1.0f) {
    color = generateRandomColor();  // Generate random color for visualization
    updateInverseMass();  // Update inverse mass based on the mass
}

// Apply a force to the rigid body
void RigidBody::applyForce(const glm::vec3 &force) {
    this->force += force;
    std::cout << "Force applied: " << this->force.x << ", " << this->force.y << ", " << this->force.z << std::endl;
    std::cout << "Inverse mass: " << inverseMass << std::endl;
    std::cout << "Acceleration (before update): " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << std::endl;
    acceleration = this->force * inverseMass;
    std::cout << "Updated acceleration: " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << std::endl;
}



// Update the physical state of the rigid body (position, velocity, etc.)
void RigidBody::integrate(float deltaTime) {
    std::cout << "Force: " << force.x << ", " << force.y << ", " << force.z << std::endl;  // 确保 force 值是正确的
    acceleration = force * inverseMass;  // F = ma, so a = F/m
    std::cout << "Acceleration: " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << std::endl;  // 检查加速度
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    force = glm::vec3(0.0f);  // Reset the force after integration
}

// Generate a random color for the rigid body (used for visualization)
glm::vec3 RigidBody::generateRandomColor() {
    return glm::vec3(static_cast<float>(rand()) / RAND_MAX,  // Random Red
                     static_cast<float>(rand()) / RAND_MAX,  // Random Green
                     static_cast<float>(rand()) / RAND_MAX); // Random Blue
}

void RigidBody::updateInverseMass() {
    inverseMass = (mass > 0.0f) ? 1.0f / mass : 0.0f;  // If mass is 0, set inverse mass to 0
    std::cout << "Inverse mass: " << inverseMass << std::endl;  // Debugging the inverseMass
}

