#include "World.h"

void World::addRigidBody(std::unique_ptr<RigidBody> body) {
    bodies.push_back(std::move(body));
}

void World::simulate(float deltaTime) {
    for (auto& body : bodies) {
        body->integrate(deltaTime); // Update rigid body position and velocity
    }

    collisionDetector.detectCollisions(bodies); // Detect and resolve collisions
}

const std::vector<std::unique_ptr<RigidBody>>& World::getBodies() const {
    return bodies;
}
