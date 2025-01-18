#include "CollisionDetector.h"

void CollisionDetector::detectCollisions(std::vector<std::unique_ptr<RigidBody>>& bodies) {
    // Collision logic for detecting bodies[i] and bodies[j]
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            // Collision Detection Logic
        }
    }
}
