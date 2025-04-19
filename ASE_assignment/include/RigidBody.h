#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include <glm/glm.hpp>
#include <cstdlib>

class RigidBody {
public:
    glm::vec3 position;     // Position of the rigid body
    glm::vec3 velocity;     // Velocity of the rigid body
    glm::vec3 acceleration; // Acceleration of the rigid body
    glm::vec3 force;        // Applied force on the rigid body
    glm::vec3 color;        // Random color assigned to the rigid body
    float mass;             // Mass of the rigid body
    float radius;           // Radius of the rigid body
    float inverseMass;      // Inverse of the mass for efficiency in calculations

    RigidBody();            // Default constructor
    RigidBody(const glm::vec3& pos); // Constructor with initial position

    void applyForce(const glm::vec3& force);
    void integrate(float deltaTime);

private:
    glm::vec3 generateRandomColor();
    void updateInverseMass();
};

#endif // RIGIDBODY_H_
