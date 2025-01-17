#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <iostream>
#include "RigidBody.h"

class World {
public:
    void addRigidBody(std::unique_ptr<RigidBody> body);
    void simulate(float deltaTime);
    void printBodies() const;
    size_t getRigidBodyCount() const;  // 提供刚体数量
    const std::vector<std::unique_ptr<RigidBody>>& getBodies() const;  // 获取刚体列表

private:
    std::vector<std::unique_ptr<RigidBody>> bodies;
};

#endif
