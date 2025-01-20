cmake_minimum_required(VERSION 3.10)

# Set OpenGL preference to GLVND
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

project(RigidBodyDynamics VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GTest REQUIRED)
find_package(fmt REQUIRED)

# Manually set GLFW include and library paths
set(GLFW_INCLUDE_DIR /home/s5722414/glfw/include)
set(GLFW_LIBRARY_DIR /home/s5722414/glfw/build/src)

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        /home/s5722414/glm
        /home/s5722414/NGL/include
        ${GLFW_INCLUDE_DIR}
)

# Link directories
link_directories(
        /home/s5722414/NGL/lib            # NGL libraries
)

# Enable GLM experimental features
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

# Add library
add_library(RigidBodyLib
        src/RigidBody.cpp
        src/World.cpp
        src/PhysicsEngine.cpp
        src/CollisionDetector.cpp
        src/Renderer.cpp
)

# Link libraries to RigidBodyLib
target_link_libraries(RigidBodyLib
        OpenGL::GL
        pthread
        dl
        NGL
        fmt::fmt
        ${GLFW_LIBRARY_DIR}/libglfw3.a
)

# Add main executable
add_executable(RigidBodyDynamics src/main.cpp)

# Link libraries to RigidBodyDynamics
target_link_libraries(RigidBodyDynamics
        RigidBodyLib
        OpenGL::GL
        pthread
        dl
        fmt::fmt
        ${GLFW_LIBRARY_DIR}/libglfw3.a
        NGL
)

# Enable testing
enable_testing()

# Add Unit Test: RigidBody
add_executable(test_rigidbody tests/test_rigidbody.cpp)
target_include_directories(test_rigidbody PRIVATE include)
target_link_libraries(test_rigidbody RigidBodyLib GTest::GTest GTest::Main pthread)

# Add Unit Test: World
add_executable(test_world tests/test_world.cpp)
target_include_directories(test_world PRIVATE include)
target_link_libraries(test_world RigidBodyLib GTest::GTest GTest::Main pthread)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_BUILD_RPATH /home/s5722414/NGL/lib)

# Print build information for debugging
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "GLM include directory: /home/s5722414/glm")
message(STATUS "NGL include directory: /home/s5722414/NGL/include")
message(STATUS "NGL library directory: /home/s5722414/NGL/lib")
message(STATUS "GLFW include directory: ${GLFW_INCLUDE_DIR}")
message(STATUS "GLFW library directory: ${GLFW_LIBRARY_DIR}")