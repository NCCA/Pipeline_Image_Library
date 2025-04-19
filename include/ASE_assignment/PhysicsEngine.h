#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "RigidBody.h"

class PhysicsEngine {
public:
    PhysicsEngine() : gravity(0.0f, -9.8f, 0.0f) {}

    void update(std::vector<std::unique_ptr<RigidBody>> &bodies, float deltaTime);
    void applyGravity(RigidBody& body, float deltaTime);
    void resolveCollision(RigidBody& body1, RigidBody& body2);
    void setGravity(const glm::vec3 &g) { gravity = g; }

private:
    glm::vec3 gravity;
};

#endif // PHYSICSENGINE_H_
