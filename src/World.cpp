#include "World.h"
#include "CollisionDetector.h"
#include "PhysicsEngine.h"


World::World() {}

void World::addRigidBody(RigidBody* body) {
    bodies.push_back(body);
}

void World::simulate(float deltaTime) {
    PhysicsEngine::update(bodies, deltaTime);
    CollisionDetector::detectCollisions(bodies);
}
