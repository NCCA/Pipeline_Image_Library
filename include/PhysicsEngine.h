#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "RigidBody.h"
#include <vector>

class PhysicsEngine {
public:
    static void update(std::vector<RigidBody*>& bodies, float deltaTime);
};

#endif
