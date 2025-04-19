#include <gtest/gtest.h>
#include "PhysicsEngine.h"
#include "RigidBody.h"

// Test case: Gravity application
TEST(PhysicsEngineTest, ApplyGravity) {
    PhysicsEngine engine;
    RigidBody body;
    body.velocity = glm::vec3(0.0f); // Initialize velocity to zero

    engine.applyGravity(body, 0.1f); // Apply gravity for 0.1 seconds
    ASSERT_FLOAT_EQ(body.velocity.y, -0.98f); // Verify the velocity change due to gravity
}

// Test case: Collision response
TEST(PhysicsEngineTest, CollisionResponse) {
    PhysicsEngine engine;

    RigidBody body1, body2;

    // Initialize positions
    body1.position = glm::vec3(-1.0f, 0.0f, 0.0f); // Body1 at (-1, 0, 0)
    body2.position = glm::vec3(1.0f, 0.0f, 0.0f);  // Body2 at (1, 0, 0)

    // Initialize velocities
    body1.velocity = glm::vec3(1.0f, 0.0f, 0.0f);  // Body1 moving towards the right
    body2.velocity = glm::vec3(-1.0f, 0.0f, 0.0f); // Body2 moving towards the left

    // Set inverse masses
    body1.inverseMass = 1.0f; // Body1 has a mass of 1
    body2.inverseMass = 1.0f; // Body2 has a mass of 1

    // Apply collision response
    engine.resolveCollision(body1, body2);

    // Verify the results
    ASSERT_FLOAT_EQ(body1.velocity.x, -1.0f); // Body1's velocity should reverse
    ASSERT_FLOAT_EQ(body2.velocity.x, 1.0f);  // Body2's velocity should reverse
}
