// CollisionDetector.h
#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <memory>
#include <vector>
#include "RigidBody.h"


class CollisionDetector {
public:
    void detectCollisions(std::vector<std::unique_ptr<RigidBody>>& bodies);
    void resolveCollision(RigidBody& body1, RigidBody& body2);
};


#endif