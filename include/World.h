#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <memory>
#include "RigidBody.h"
#include "CollisionDetector.h"
#include "Ground.h"
#include "PhysicsEngine.h"
#include "Renderer.h"

class World {
public:
    World();  // Constructor to initialize the world
    ~World(); // Destructor for proper cleanup

    // Methods for adding rigid bodies
    void addRigidBodies();  // Adds multiple rigid bodies
    void addRigidBody(std::unique_ptr<RigidBody> body); // Adds a single rigid body

    // Physics simulation and rendering methods
    void simulate(float deltaTime); // Simulates the physics for one time step
    void render(const glm::mat4 &view, const glm::mat4 &projection); // Renders the scene

    // Methods to retrieve rigid bodies
    RigidBody* getRigidBody(size_t index) const; // Returns a pointer to a specific rigid body by index
    size_t getBodiesCount() const { return bodies.size(); } // Returns the count of rigid bodies
    const RigidBody* getBodyPtr(size_t i) const { return bodies[i].get(); } // Returns the pointer to a specific rigid body
    const std::vector<std::unique_ptr<RigidBody>>& getBodies() const { return bodies; } // Returns all rigid bodies

    // Method to calculate the distance between a rigid body and the ground
    float getDistanceToGround(size_t bodyIndex) const;

    // Method to initialize rigid bodies with random parameters
    void initializeRigidBodies(std::vector<std::unique_ptr<RigidBody>> &bodies, float groundY, float planeSize, int count);

    // Method to generate a random color
    glm::vec3 generateRandomColor();

private:
    std::vector<std::unique_ptr<RigidBody>> bodies; // Container for all rigid bodies
    std::unique_ptr<Ground> ground; // Ground object for collision detection
    std::vector<std::unique_ptr<RigidBody>> rigidBodies; // Container for rigid body instances
    CollisionDetector collisionDetector; // Collision detection engine
    PhysicsEngine physicsEngine; // Physics engine for handling updates
    Renderer renderer; // Renderer for visualizing the simulation
};

#endif // WORLD_H_
