#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H
#include "CollisionDetector.h"


#include "RigidBody.h"
#include <vector>

class CollisionDetector {
public:
    static void detectCollisions(std::vector<RigidBody*>& bodies);
};

#endif
