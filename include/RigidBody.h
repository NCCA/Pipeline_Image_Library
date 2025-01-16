#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

class RigidBody {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;

    RigidBody();
    void applyForce(const glm::vec3& force);
    void update(float deltaTime);
};

#endif
