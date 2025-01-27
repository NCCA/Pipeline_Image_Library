#include "PhysicsEngine.h"
#include <glm/glm.hpp>

// Update physics for all rigid bodies in the world (applying gravity, updating velocity, and position)
void PhysicsEngine::update(std::vector<std::unique_ptr<RigidBody>> &bodies, float deltaTime) {
    for (auto &body : bodies) {
        // Apply gravity force to the body
        body->force += gravity * body->mass;

        // Update velocity and position based on the forces acting on the body
        body->velocity += body->force / body->mass * deltaTime;
        body->position += body->velocity * deltaTime;

        // Clear the force after applying it
        body->force = glm::vec3(0, 0, 0);
    }
}

// Apply gravity to a single body (independent of world gravity)
void PhysicsEngine::applyGravity(RigidBody& body, float deltaTime) {
    const float gravity = -9.8f; // Acceleration due to gravity
    body.velocity.y += gravity * deltaTime; // Update only the vertical component (y-axis)
}

// Resolve collision between two rigid bodies (elastic collision response)
void PhysicsEngine::resolveCollision(RigidBody& body1, RigidBody& body2) {
    // Compute the relative velocity between two bodies
    glm::vec3 relativeVelocity = body1.velocity - body2.velocity;

    // Compute the collision normal (direction vector from body1 to body2)
    glm::vec3 collisionNormal = glm::normalize(body1.position - body2.position);

    // Compute the velocity component along the normal direction (dot product)
    float velocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);

    // If the velocity along the normal is positive, the bodies are moving away from each other
    if (velocityAlongNormal > 0) return; // No collision resolution needed

    // Coefficient of restitution (1.0 for a perfectly elastic collision)
    float restitution = 1.0f;

    // Calculate the impulse magnitude using the velocity along the normal and restitution
    float impulseMagnitude = -(1 + restitution) * velocityAlongNormal;
    impulseMagnitude /= body1.inverseMass + body2.inverseMass;

    // Calculate the impulse vector to apply
    glm::vec3 impulse = impulseMagnitude * collisionNormal;

    // Apply the impulse to both bodies (inverse mass for proper scaling)
    body1.velocity += impulse * body1.inverseMass;
    body2.velocity -= impulse * body2.inverseMass;
}


