#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <glm/glm.hpp>

class RigidBody {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    RigidBody();
    float mass = 1.0f;
    float radius = 1.0f; // Suppose the rigid body is a sphere

    float rotationAngle = 0.0f; // // Rotation angle
    glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f); //Default rotation around the Y-axis

    void applyForce(const glm::vec3& force);
    void integrate(float deltaTime);
};

#endif