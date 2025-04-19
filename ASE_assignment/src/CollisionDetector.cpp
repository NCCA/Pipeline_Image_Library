#include "CollisionDetector.h"
#include <glm/glm.hpp>
#include <algorithm>
#include <iostream>

void CollisionDetector::detectCollisions(std::vector<std::unique_ptr<RigidBody>>& bodies, const Ground& ground) {
    // Detect AABB collisions between rigid bodies
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            AABB aabb1(
                bodies[i]->position - glm::vec3(bodies[i]->radius),
                bodies[i]->position + glm::vec3(bodies[i]->radius)
            );
            AABB aabb2(
                bodies[j]->position - glm::vec3(bodies[j]->radius),
                bodies[j]->position + glm::vec3(bodies[j]->radius)
            );

            // If AABB overlap, it is considered a collision
            if (AABB::intersects(aabb1, aabb2)) {
                resolveCollision(*bodies[i], *bodies[j]);
            }
        }
    }

    // Detect collisions between rigid bodies and the ground
    for (auto &body : bodies) {
        AABB bodyAABB(
            body->position - glm::vec3(body->radius),
            body->position + glm::vec3(body->radius)
        );

        // Intersects with ground AABB
        if (AABB::intersects(bodyAABB, ground.aabb)) {
            resolveGroundCollision(*body, ground);
        }
    }
}

void CollisionDetector::resolveCollision(RigidBody &body1, RigidBody &body2) {
    glm::vec3 normal = glm::normalize(body2.position - body1.position);
    float relativeVelocity = glm::dot(body2.velocity - body1.velocity, normal);

    // If the relative speed is greater than 0, it means that the separation is taking place and no processing is required.
    if (relativeVelocity > 0) return;

    float restitution = 1.0f; // Fully elastic
    float impulseMagnitude = -(1.0f + restitution) * relativeVelocity /
                            (1.0f / body1.mass + 1.0f / body2.mass);

    glm::vec3 impulse = impulseMagnitude * normal;
    body1.velocity -= impulse / body1.mass;
    body2.velocity += impulse / body2.mass;
}

void CollisionDetector::resolveGroundCollision(RigidBody &body, const Ground &ground) {
    // Assume the ground normal is y = 1
    glm::vec3 groundNormal(0.0f, 1.0f, 0.0f);
    float relativeVelocity = glm::dot(body.velocity, groundNormal);

    if (relativeVelocity > 0) return; // Rigid body is moving upwards or stationary

    float restitution = 1.0f;
    float impulseMagnitude = -(1.0f + restitution) * relativeVelocity / (1.0f / body.mass);

    glm::vec3 impulse = impulseMagnitude * groundNormal;
    body.velocity += impulse / body.mass;

    // Adjust the rigid body y-coordinate to avoid penetrating the ground
    body.position.y = ground.aabb.maxp.y + body.radius;
}

bool CollisionDetector::detectBoundaryCollision(const RigidBody& body, float boundarySize) {
    // Simple boundary detection
    return (glm::abs(body.position.x) > boundarySize ||
            glm::abs(body.position.y) > boundarySize ||
            glm::abs(body.position.z) > boundarySize);
}

bool CollisionDetector::detectRigidBodyCollision(const RigidBody& body1, const RigidBody& body2, float deltaTime) {
    // Simple distance detection
    float distance = glm::length(body1.position - body2.position);
    return distance < (body1.radius + body2.radius);
}
