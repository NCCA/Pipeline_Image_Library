#include "RigidBody.h"

RigidBody::RigidBody() : position(0), velocity(0), acceleration(0), mass(1.0f) {}

void RigidBody::applyForce(const glm::vec3& force) {
    acceleration += force / mass;
}

void RigidBody::update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    acceleration = glm::vec3(0);
}
