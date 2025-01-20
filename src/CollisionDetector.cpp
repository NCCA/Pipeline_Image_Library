#include "CollisionDetector.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

void CollisionDetector::detectCollisions(std::vector<std::unique_ptr<RigidBody>>& bodies) {
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            auto& body1 = bodies[i];
            auto& body2 = bodies[j];

            float distance = glm::length(body1->position - body2->position);
            float combinedRadius = body1->radius + body2->radius;

            if (distance <= combinedRadius) {
                // Calculate the normal vector
                glm::vec3 collisionNormal = glm::normalize(body2->position - body1->position);
                glm::vec3 relativeVelocity = body2->velocity - body1->velocity;
                float velocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);

                if (velocityAlongNormal > 0) continue; // Skip if rigid body is moving away

                // Elastic collision factor (1 for full elasticity)
                float restitution = 1.0f;

                // Calculate the impulse
                float j = -(1 + restitution) * velocityAlongNormal;
                j /= (1 / body1->mass + 1 / body2->mass);

                glm::vec3 impulse = j * collisionNormal;

                // Update speed
                body1->velocity -= impulse / body1->mass;
                body2->velocity += impulse / body2->mass;
            }
        }
    }
}
