#include <iostream>
#include "World.h"


int main() {
    World world;

    RigidBody* body1 = new RigidBody();
    body1->position = glm::vec3(0, 10, 0);
    body1->applyForce(glm::vec3(0, -9.8f, 0));
    world.addRigidBody(body1);

    RigidBody* body2 = new RigidBody();
    body2->position = glm::vec3(0, 20, 0);
    body2->applyForce(glm::vec3(0, -9.8f, 0));
    world.addRigidBody(body2);

    for (int i = 0; i < 100; ++i) {
        world.simulate(0.016f);

        std::cout << "Body1 position: " << body1->position.y << std::endl;
    }

    delete body1;
    delete body2;

    return 0;
}
