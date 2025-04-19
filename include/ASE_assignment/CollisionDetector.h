#ifndef COLLISIONDETECTOR_H_
#define COLLISIONDETECTOR_H_

#include <memory>
#include <vector>
#include "RigidBody.h"
#include "AABB.h"
#include "Ground.h"

class CollisionDetector {
public:
    void detectCollisions(std::vector<std::unique_ptr<RigidBody>> &bodies, const Ground &ground);
    void resolveCollision(RigidBody &body1, RigidBody &body2);
    void resolveGroundCollision(RigidBody &body, const Ground &ground);
    bool detectBoundaryCollision(const RigidBody& body, float boundarySize);
    bool detectRigidBodyCollision(const RigidBody& body1, const RigidBody& body2, float deltaTime);
};

#endif // COLLISIONDETECTOR_H_
