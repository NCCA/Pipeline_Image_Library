#include "CollisionDetector.h"

void CollisionDetector::detectCollisions(std::vector<std::unique_ptr<RigidBody>>& bodies) {
    // 检测 bodies[i] 和 bodies[j] 的碰撞逻辑
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            // 碰撞检测逻辑
        }
    }
}
