#include <gtest/gtest.h>
#include "World.h"
#include "RigidBody.h"
#include "Renderer.h" // Include for the random color generation function

// Test case: Precise free fall simulation
TEST(WorldTest, PreciseFreeFall) {
    World world;

    // Add a rigid body to the world
    world.addRigidBody(std::make_unique<RigidBody>(glm::vec3(0, 10, 0)));

    float deltaTime = 0.001f; // Simulation time step (1ms)
    for (int i = 0; i < 1000; ++i) { // Simulate for 1000 steps
        world.simulate(deltaTime);
    }

    // Get the final position and velocity of the rigid body
    float finalY = world.getRigidBody(0)->position.y;
    float finalV = world.getRigidBody(0)->velocity.y;

    // Theoretical values for position and velocity
    float y_theory = 10.0f + 0.5f * -9.8f * (1000 * deltaTime) * (1000 * deltaTime); // s = ut + 0.5at²
    float v_theory = -9.8f * (1000 * deltaTime); // v = u + at

    // Check if the simulation results are close to theoretical values
    EXPECT_NEAR(finalY, y_theory, 0.3f); // Allow small tolerance
    EXPECT_NEAR(finalV, v_theory, 0.3f);
}

// Test case: Verify that random colors are unique for different rigid bodies
TEST(WorldTest, RandomColors) {
    RigidBody body1, body2;
    body1.position = glm::vec3(0.0f, 5.0f, 0.0f); // Set position for body1
    body1.radius = 1.0f; // Set radius for body1
    body1.color = generateRandomColor(); // Assign a random color to body1

    body2.position = glm::vec3(0.0f, 10.0f, 0.0f); // Set position for body2
    body2.radius = 1.0f; // Set radius for body2
    body2.color = generateRandomColor(); // Assign a random color to body2

    ASSERT_NE(body1.color, body2.color); // Check if the two colors are different
}
