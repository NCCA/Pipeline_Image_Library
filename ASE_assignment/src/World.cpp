#include "World.h"
#include <iostream>
#include <random>  // Include random number library
#include "Renderer.h"
#include "RigidBody.h"

// Constructor to initialize the world
World::World()
{
    // Initialize the ground with a specified position and size
    ground = std::make_unique<Ground>(
        glm::vec3(0.f, -5.f, 0.f),   // Ground position
        glm::vec3(50.f, 1.f, 50.f)   // Ground size (width, height, depth)
    );
}

// Destructor (default)
World::~World() {}

// Add a rigid body to the world
void World::addRigidBody(std::unique_ptr<RigidBody> body) {
    bodies.push_back(std::move(body));  // Add the rigid body to the vector
}

// Add multiple rigid bodies to the world
void World::addRigidBodies() {
    const float groundY = ground->aabb.maxp.y;  // Get the ground level (Y-coordinate)
    const float planeSize = 50.0f;              // Size of the plane
    const int ballCount = 10;                   // Number of balls to create

    initializeRigidBodies(bodies, groundY, planeSize, ballCount);  // Initialize rigid bodies
}

// Initialize rigid bodies with random positions, velocities, etc.
void World::initializeRigidBodies(std::vector<std::unique_ptr<RigidBody>> &bodies,
                                   float groundY, float planeSize, int count) {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist_xz(-planeSize / 2, planeSize / 2);  // Random X and Z
    std::uniform_real_distribution<float> dist_y(groundY + 10.0f, groundY + 20.0f);  // Y position above the ground

    for (int i = 0; i < count; ++i) {
        // Create a new rigid body
        auto body = std::make_unique<RigidBody>();
        body->position = glm::vec3(dist_xz(gen), dist_y(gen), dist_xz(gen)); // Set random position
        body->velocity = glm::vec3(0.0f, 0.0f, 0.0f);                       // Initial velocity
        body->radius = 1.0f + static_cast<float>(rand()) / RAND_MAX * 2.0f; // Random radius between 1 and 3
        body->mass = 1.0f;                                                 // Mass
        body->color = generateRandomColor();                               // Random color for visualization
        bodies.push_back(std::move(body));                                 // Add body to the vector
    }
}

// Simulate the physics of the world (update positions, handle collisions)
void World::simulate(float deltaTime) {
    // Update physics for each rigid body
    physicsEngine.update(bodies, deltaTime);

    // Handle collision detection
    collisionDetector.detectCollisions(bodies, *ground);
}

// Render the world (including the rigid bodies and ground)
void World::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    // 1) Calculate the ground's position
    float groundY = ground->aabb.minp.y;  // Ground's Y position
    float halfSize = (ground->aabb.maxp.x - ground->aabb.minp.x) * 0.5f; // Half size of the ground

    // 2) Render the ground
    renderer.renderGround(groundY, halfSize, view, proj);

    // 3) Render all the rigid bodies
    renderer.render(bodies, view, proj);
}

// Calculate the distance from the specified rigid body to the ground
float World::getDistanceToGround(size_t bodyIndex) const
{
    if (bodyIndex >= bodies.size()) return 0.0f; // Return 0 if the index is out of range

    // Get the ground level (Y position of the ground)
    float groundLevel = ground->aabb.maxp.y;

    // Calculate the lowest point of the rigid body (position.y - radius)
    float lowestPoint = bodies[bodyIndex]->position.y - bodies[bodyIndex]->radius;

    // Return the distance between the rigid body's lowest point and the ground
    return (lowestPoint - groundLevel);
}

// Get a rigid body at a specific index
RigidBody* World::getRigidBody(size_t index) const {
    if (index >= bodies.size()) {
        throw std::out_of_range("RigidBody index out of range");  // Throw an exception if index is invalid
    }
    return bodies[index].get();  // Return the rigid body at the specified index
}

// Helper function to generate a random color
glm::vec3 World::generateRandomColor() {
    return glm::vec3(static_cast<float>(rand()) / RAND_MAX,  // Random Red component
                     static_cast<float>(rand()) / RAND_MAX,  // Random Green component
                     static_cast<float>(rand()) / RAND_MAX); // Random Blue component
}
