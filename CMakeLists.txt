# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Specify the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/home/s5722414/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Project details
project(RigidBodyDynamics VERSION 1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Print project details to the console
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Include directories for header files
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
        ${GTEST_INCLUDE_DIRS}
)

# Link directories for libraries
link_directories(
        ${SDL2_LIBRARY_DIRS}
)

# Define the source files for the project
set(SOURCE_FILES
        src/AABB.cpp
        src/CollisionDetector.cpp
        src/PhysicsEngine.cpp
        src/Renderer.cpp
        src/RigidBody.cpp
        src/Ground.cpp
        src/World.cpp
        src/main.cpp
)

# Create the executable for the main application
add_executable(RigidBodyDynamics ${SOURCE_FILES})

# Link necessary libraries to the executable
target_link_libraries(RigidBodyDynamics
        PRIVATE
        ${OPENGL_gl_LIBRARY}
        ${SDL2_LIBRARIES}
        GLEW::GLEW
        dl
        pthread
)

# Enable testing
enable_testing()

# Define test sources for common files used in tests
set(TEST_COMMON_SOURCES
        src/AABB.cpp
        src/RigidBody.cpp
)

# Test for RigidBody
add_executable(test_rigidbody
        tests/test_rigidbody.cpp
        ${TEST_COMMON_SOURCES}
)
target_link_libraries(test_rigidbody
        PRIVATE
        GTest::gtest_main
        pthread
)
add_test(NAME TestRigidBody COMMAND test_rigidbody)

# Test for PhysicsEngine
add_executable(test_physics_engine
        tests/test_physics_engine.cpp
        src/PhysicsEngine.cpp
        ${TEST_COMMON_SOURCES}
)
target_link_libraries(test_physics_engine
        PRIVATE
        GTest::gtest_main
        pthread
)
add_test(NAME TestPhysicsEngine COMMAND test_physics_engine)

# Test for World
add_executable(test_world
        tests/test_world.cpp
        src/World.cpp
        src/CollisionDetector.cpp
        src/PhysicsEngine.cpp
        src/Ground.cpp
        src/Renderer.cpp
        ${TEST_COMMON_SOURCES}
)
target_link_libraries(test_world
        PRIVATE
        GTest::gtest_main
        pthread
        ${OPENGL_gl_LIBRARY}
        ${SDL2_LIBRARIES}
        GLEW::GLEW
        dl
)
add_test(NAME TestWorld COMMAND test_world)  # Add test for World
