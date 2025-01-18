
cmake_minimum_required(VERSION 3.10)


project(RigidBodyDynamics VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Includes GLEW, GLFW, GLM and Google Test
find_package(OpenGL REQUIRED)
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        /home/s5722414/local/usr/local/include  
        /home/s5722414/glfw/include            
        /home/s5722414/glm                     
)

# Link library catalogue
link_directories(
        /home/s5722414/local/usr/local/lib64   
        /home/s5722414/glfw/build/src          
)

# Setting up project source files
set(SOURCE_FILES
        src/main.cpp
        src/World.cpp
        src/RigidBody.cpp
        src/PhysicsEngine.cpp
        src/CollisionDetector.cpp
        src/Renderer.cpp
)

# Setup headers
set(HEADER_FILES
        include/World.h
        include/RigidBody.h
        include/PhysicsEngine.h
        include/CollisionDetector.h
        include/Renderer.h
)

# Add vertex and fragment shaders
file(GLOB SHADERS shaders/*.glsl)

# Main executable
add_executable(RigidBodyDynamics ${SOURCE_FILES} ${HEADER_FILES} ${SHADERS})


target_link_libraries(RigidBodyDynamics
        /home/s5722414/local/usr/local/lib64/libGLEW.so  
        /home/s5722414/glfw/build/src/libglfw3.a        
        OpenGL::GL                                       
        pthread                                         
        dl                                              
)

# Enable testing
enable_testing()

# search Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Adding Unit Tests - RigidBody
add_executable(test_rigidbody tests/test_rigidbody.cpp
        src/RigidBody.cpp
)
target_include_directories(test_rigidbody PRIVATE include)
target_link_libraries(test_rigidbody ${GTEST_BOTH_LIBRARIES} pthread)

# Adding Unit Tests - World
add_executable(test_world tests/test_world.cpp
        src/World.cpp
        src/RigidBody.cpp
)
target_include_directories(test_world PRIVATE include)
target_link_libraries(test_world ${GTEST_BOTH_LIBRARIES} pthread)

# Adding Test Objectives
add_test(NAME TestRigidBody COMMAND test_rigidbody)
add_test(NAME TestWorld COMMAND test_world)

# Printing path information for GLEW and GLFW
message(STATUS "GLEW include directory: /home/s5722414/local/usr/local/include")
message(STATUS "GLEW library directory: /home/s5722414/local/usr/local/lib64")
message(STATUS "GLFW include directory: /home/s5722414/glfw/include")
message(STATUS "GLFW library directory: /home/s5722414/glfw/build/src")
