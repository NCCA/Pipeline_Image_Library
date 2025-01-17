//PhysicsEngine.h
#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <memory>
#include "RigidBody.h"

class PhysicsEngine {
public:
    void update(std::vector<std::unique_ptr<RigidBody>>& bodies, float deltaTime);
};

#endif // PHYSICSENGINE_H
