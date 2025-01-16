#include "PhysicsEngine.h"

void PhysicsEngine::update(std::vector<RigidBody*>& bodies, float deltaTime) {
    for (auto& body : bodies) {
        body->update(deltaTime);
    }
}
