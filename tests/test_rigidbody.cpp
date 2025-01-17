#include <gtest/gtest.h>
#include "RigidBody.h"

TEST(RigidBodyTest, IntegrationTest) {
    RigidBody body;
    body.velocity = glm::vec3(1.0f, 0.0f, 0.0f);
    body.integrate(1.0f);
    EXPECT_FLOAT_EQ(body.position.x, 1.0f);
}
