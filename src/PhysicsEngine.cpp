#include "PhysicsEngine.h"

void PhysicsEngine::update(std::vector<std::unique_ptr<RigidBody>>& bodies, float deltaTime) {
    for (auto& body : bodies) {
        body->integrate(deltaTime);
    }
}
