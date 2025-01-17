#include "World.h"

void World::addRigidBody(std::unique_ptr<RigidBody> body) {
    bodies.push_back(std::move(body));
}

void World::simulate(float deltaTime) {
    for (auto& body : bodies) {
        body->integrate(deltaTime);
    }
}

void World::printBodies() const {
    for (size_t i = 0; i < bodies.size(); ++i) {
        std::cout << "Body " << i + 1 << " position: "
                  << bodies[i]->position.y << std::endl;
    }
}

size_t World::getRigidBodyCount() const {
    return bodies.size();
}

const std::vector<std::unique_ptr<RigidBody>>& World::getBodies() const {
    return bodies;
}
