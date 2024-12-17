[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RM1pL2Qm)

Rigid Body Dynamics Simulation

Project Overview:
This project simulates the dynamics of a rigid body and demonstrates the behaviour of a rigid body under the influence of forces and collisions.

Functions:
Rigid body motion and rotation
Gravity and external force simulation
Collision detection and response
OpenGL graphics visualisation

Design and Data Structures - Class Design:
1. RigidBody - class representing a rigid body, containing properties such as position, velocity, force, etc.
2. PhysicsEngine- The physics engine that computes the motion and collision of the rigid body.
3. Renderer - responsible for rendering the rigid body using OpenGL/NGL.
4. CollisionDetector- Handles collision detection and response.

Physics Equation:

Equation of motion: F = ma

Velocity update: v = v0 + at

Position update: x = x0 + vt + 0.5at^2

Collision response: based on conservation of momentum with rebound coefficients.

 Unit Testing - Developing core functionality using TDD:
1. computation of motion of a rigid body under force
2. collision detection and response
3. Gravity and external force simulation
