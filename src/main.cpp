#include "World.h"
#include "RigidBody.h"
#include <iostream>

int main() {
    World world;

    auto body1 = std::make_unique<RigidBody>();
    body1->position = glm::vec3(0, 10, 0);
    body1->applyForce(glm::vec3(0, -9.8f, 0));
    world.addRigidBody(std::move(body1));

    for (int i = 0; i < 100; ++i) {
        world.simulate(0.016f);
        world.printBodies();
    }

    return 0;
}
