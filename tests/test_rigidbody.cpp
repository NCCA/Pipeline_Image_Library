#include <gtest/gtest.h>
#include "RigidBody.h"

TEST(RigidBodyTest, ApplyForceTest) {
    RigidBody body;
    body.mass = 1.0f;
    body.applyForce(glm::vec3(0.0f, 2.0f, 0.0f));

    std::cout << "Test - Acceleration: " << body.acceleration.x << ", " << body.acceleration.y << ", " << body.acceleration.z << std::endl;

    EXPECT_FLOAT_EQ(body.acceleration.x, 0.0f);
    EXPECT_FLOAT_EQ(body.acceleration.y, 2.0f);
    EXPECT_FLOAT_EQ(body.acceleration.z, 0.0f);
}

TEST(RigidBodyTest, IntegrateTest) {
    RigidBody body;
    body.mass = 1.0f;
    body.applyForce(glm::vec3(0, -9.8f, 0));
    body.integrate(1.0f);
    // velocity = (0, -9.8, 0), position = (0, -9.8, 0)
    EXPECT_FLOAT_EQ(body.velocity.y, -9.8f);
    EXPECT_FLOAT_EQ(body.position.y, -9.8f);
}
