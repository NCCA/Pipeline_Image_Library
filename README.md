# RigidBodyDynamics: A Simple Rigid Body Dynamics Simulation

## Project Description

**RigidBodyDynamics** is a C++ project that simulates rigid body motion with real-time rendering using OpenGL. The simulation focuses on physically accurate dynamics, including collision detection and resolution, supported by Axis-Aligned Bounding Boxes (AABB) and impulse-based collision responses. It also provides interactive features for users to add objects or debug their behaviors dynamically.

---

## Features

- **Collision Detection**:
    - Broad-phase detection using AABB to determine potential collisions efficiently.
    - Narrow-phase detection for precise collision checks between objects.

- **Collision Response**:
    - Impulse-based resolution for physically accurate post-collision velocities.
    - Ground collision handling to prevent objects from penetrating the surface.

- **Real-Time Rendering**:
    - OpenGL-based visualization of spheres and a ground plane.
    - Randomized sphere colors for improved visualization.

- **User Interaction**:
    - Add new rigid bodies dynamically using the keyboard.
    - Debug and analyze object properties during runtime.

---

## Design

### Data Structures and Classes

The project is implemented using an object-oriented design. Below is an overview of key classes:

- **`RigidBody`**:
  Represents a single rigid body with properties like position, velocity, acceleration, mass, and radius. Includes methods for applying forces and integrating motion.

- **`World`**:
  Manages all rigid bodies and the simulation environment. Handles adding rigid bodies, simulating physics, and rendering the scene.

- **`PhysicsEngine`**:
  Updates the motion of rigid bodies, applies gravity, and handles collision resolution.

- **`CollisionDetector`**:
  Detects collisions between rigid bodies and the ground. Resolves collisions to ensure objects behave realistically.

- **`Renderer`**:
  Handles OpenGL rendering, including drawing spheres, ground planes, and applying visual properties like random colors.

### Algorithms

- **Collision Detection**:
    - **AABB** is used for efficient collision detection between objects and the ground.
    - Pairwise narrow-phase checks ensure accurate detection for overlapping objects.

- **Collision Response**:
    - Uses an impulse-based method to calculate new velocities for colliding objects.
    - Fully elastic collisions (restitution = 1.0) are assumed for simplicity.

- **Rendering**:
    - OpenGL is used to draw objects in real-time.
    - Randomized sphere colors enhance the visual appeal of the simulation.

---

## User Interaction Controls

### Keyboard Controls

- **Spacebar**:  
  Adds a new rigid body (sphere) to the simulation.
    - The sphere is placed at a random position above the highest existing sphere.
    - It has a random initial velocity and color.  
      Example console output when pressing Space:
      [User] Added a new rigid body at (10.23, 15.0, -5.67), velocity= (2.4, -2.0, 1.5)

- **D Key**:  
  Prints the distance from each rigid body to the ground in the console.  
  Example console output when pressing D:
  Body 0 distance to ground = 3.42 Body 1 distance to ground = 7.89

---
## Build Configuration

### Use of Absolute Paths

In this project, **absolute paths** are utilized within the `CMakeLists.txt` and build scripts. The primary reasons for using absolute paths are:

1. **Dependency Management**:
- Absolute paths ensure that the compiler and linker can reliably locate external libraries and dependencies, such as SDL2, GLEW, and OpenGL, especially when these libraries are installed in non-standard directories or managed by package managers like vcpkg.

2. **Consistency Across Environments**:
- By specifying absolute paths, the build process remains consistent regardless of the current working directory, reducing the likelihood of build errors related to missing or incorrectly located dependencies.

3. **Ease of Integration with External Tools**:
- Tools like vcpkg often provide absolute paths to installed libraries, making it straightforward to integrate these dependencies into the CMake build system without additional configuration.

4. **Avoiding Relative Path Issues**:
- Relative paths can become problematic in complex projects with multiple nested directories. Absolute paths eliminate ambiguity, ensuring that the correct files and libraries are referenced.

**Example in `CMakeLists.txt`**:
```cmake

# Specify the path to vcpkg toolchain file if using vcpkg for dependency management
set(CMAKE_TOOLCHAIN_FILE "/public/devel/24-25/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Find packages using absolute paths
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GTest REQUIRED)

# Include directories with absolute paths
include_directories(/home/s5722414/Documents/RigidBodyDynamics/include)
include_directories(/public/devel/24-25/vcpkg/installed/x64-linux/include)

# Link libraries using absolute paths
target_link_libraries(RigidBodyDynamics 
  /public/devel/24-25/vcpkg/installed/x64-linux/lib/libGLEWd.a 
  /usr/lib64/libGL.so 
  /usr/lib64/libGLU.so 
  /usr/lib64/libX11.so 
  /usr/lib64/libXext.so 
  /public/devel/24-25/vcpkg/installed/x64-linux/lib/libSDL2d.a
  # Add other necessary libraries
)

---

## Installation and Usage

### Prerequisites

Before running the project, ensure the following tools and libraries are installed:

- **C++ Compiler**: A modern C++ compiler supporting C++17.
- **CMake**: For project configuration and build.
- **SDL2**: For window management.
- **GLEW**: For OpenGL extensions.
- **OpenGL**: For rendering graphics.

### Building the Project

1. Clone the repository:
 ```bash
 git clone git@github.com:NCCA/programming-project-Flora9822.git
 cd RigidBodyDynamics
2.Create a build directory and configure the project using CMake:
3.mkdir build
4.cd build
5.cmake ..
6.Build the project:
7.cmake --build .
Running the Application
Run the executable generated after building:
./RigidBodyDynamics
Testing the Application
Unit tests are included to ensure functionality:
./test_physics_engine
./test_world

Example Output
When running the application, you should see a window displaying a ground plane and multiple spheres. Users can interact by:
-Pressing Spacebar to add new spheres.
-Pressing D Key to debug distances of objects from the ground.

Limitations and Future Work
Current Limitations
-AABB-based collision detection may result in false positives for complex scenes.
-Only simple impulse-based collision responses are implemented (elastic collisions).
-Rendering is limited to basic objects (spheres and a plane).
Opportunities for Improvement
-Bounding Volume Hierarchies (BVH): To improve collision detection efficiency.
-Shock Propagation: To enhance stability for stacked or multi-contact scenarios.
-GUI: Add controls for spawning objects or tweaking parameters interactively.
-Shaders: Incorporate advanced shading techniques for improved visual effects.

References
1.30dayscoding.com. (2024). Mastering Game Physics: Implementing Realistic Simulations. [Online] Available at: link.
2.Bender, J., Erleben, K., and Trinkle, J. (2013). Interactive Simulation of Rigid Body Dynamics in Computer Graphics. Computer Graphics Forum, 33(1), pp.246–270. doi:https://doi.org/10.1111/cgf.12272.
3.Featherstone, R. (2008). Rigid Body Dynamics Algorithms. [Online] Available at: link.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](./LICENSE) file for details.
