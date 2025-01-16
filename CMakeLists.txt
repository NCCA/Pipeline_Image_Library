cmake_minimum_required(VERSION 3.10)
project(RigidBodyDynamics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(/home/s5722414/glm)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES

        src/World.cpp
        src/RigidBody.cpp
)

add_executable(RigidBodyDynamics
        src/main.cpp
        src/World.cpp
        src/RigidBody.cpp
        include/PhysicsEngine.h

        src/PhysicsEngine.cpp
        src/CollisionDetector.cpp
        include/CollisionDetector.h

)