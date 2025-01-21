#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "RigidBody.h"
#include "CollisionDetector.h"

class World {
public:
    // Add a rigid body to the world
    void addRigidBody(std::unique_ptr<RigidBody> body);

    // Modelling the behaviour of the entire physical world
    void simulate(float deltaTime);

    // Get list of rigid bodies (read-only access)
    const std::vector<std::unique_ptr<RigidBody>>& getBodies() const;

private:
    std::vector<std::unique_ptr<RigidBody>> bodies;  // Save all rigid bodies
    CollisionDetector collisionDetector;             // Collision Detector
};

#endif // WORLD_H
