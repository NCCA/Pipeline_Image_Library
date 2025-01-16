#ifndef WORLD_H
#define WORLD_H

#include "RigidBody.h"
#include <vector>

class World {
public:
    World();
    void addRigidBody(RigidBody* body);
    void simulate(float deltaTime);

private:
    std::vector<RigidBody*> bodies;
};

#endif
