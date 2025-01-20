#include "RigidBody.h"


RigidBody::RigidBody()
    : position(0.0f), velocity(0.0f), acceleration(0.0f), mass(1.0f), radius(1.0f) {}


void RigidBody::applyForce(const glm::vec3& force) {
    acceleration += force / mass;
}

void RigidBody::integrate(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    acceleration = glm::vec3(0.0f); // Reset acceleration
}
