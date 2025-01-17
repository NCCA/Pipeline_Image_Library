#include <gtest/gtest.h>
#include "World.h"

TEST(WorldTest, AddRigidBody) {
    World world;
    auto body = std::make_unique<RigidBody>();
    world.addRigidBody(std::move(body));
    EXPECT_EQ(world.getRigidBodyCount(), 1);
}
