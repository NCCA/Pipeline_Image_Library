#include <gtest/gtest.h>
#include "World.h"

TEST(WorldTest, CollisionDetection) {
    World world;

    auto body1 = std::make_unique<RigidBody>();
    body1->position = glm::vec3(0, 10, 0);
    body1->radius = 1.0f;
    world.addRigidBody(std::move(body1));

    auto body2 = std::make_unique<RigidBody>();
    body2->position = glm::vec3(0, 9, 0);
    body2->radius = 1.0f;
    world.addRigidBody(std::move(body2));

    world.simulate(0.016f);

    EXPECT_NE(body1->velocity.y, 0.0f);
    EXPECT_NE(body2->velocity.y, 0.0f);
}
