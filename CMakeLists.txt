# 设置最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(RigidBodyDynamics VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置构建类型（默认Debug）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 打印配置信息
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 包含GLEW、GLFW、GLM和Google Test
find_package(OpenGL REQUIRED)
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        /home/s5722414/local/usr/local/include  # GLEW 头文件目录
        /home/s5722414/glfw/include            # GLFW 头文件目录
        /home/s5722414/glm                     # GLM 头文件目录
)

# 链接库目录
link_directories(
        /home/s5722414/local/usr/local/lib64   # GLEW 静态库目录
        /home/s5722414/glfw/build/src          # GLFW 静态库目录
)

# 设置项目源文件
set(SOURCE_FILES
        src/main.cpp
        src/World.cpp
        src/RigidBody.cpp
        src/PhysicsEngine.cpp
        src/CollisionDetector.cpp
        src/Renderer.cpp
)

# 设置头文件
set(HEADER_FILES
        include/World.h
        include/RigidBody.h
        include/PhysicsEngine.h
        include/CollisionDetector.h
        include/Renderer.h
)

# 添加顶点和片段着色器（非编译文件，仅用于项目结构组织）
file(GLOB SHADERS shaders/*.glsl)

# 主可执行文件
add_executable(RigidBodyDynamics ${SOURCE_FILES} ${HEADER_FILES} ${SHADERS})

# 链接所需的库
target_link_libraries(RigidBodyDynamics
        /home/s5722414/local/usr/local/lib64/libGLEW.so  # GLEW 库
        /home/s5722414/glfw/build/src/libglfw3.a         # GLFW 库
        OpenGL::GL                                       # OpenGL
        pthread                                          # 线程库
        dl                                               # 动态链接库
)

# 启用测试
enable_testing()

# 查找Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 添加单元测试 - RigidBody
add_executable(test_rigidbody tests/test_rigidbody.cpp
        src/RigidBody.cpp
)
target_include_directories(test_rigidbody PRIVATE include)
target_link_libraries(test_rigidbody ${GTEST_BOTH_LIBRARIES} pthread)

# 添加单元测试 - World
add_executable(test_world tests/test_world.cpp
        src/World.cpp
        src/RigidBody.cpp
)
target_include_directories(test_world PRIVATE include)
target_link_libraries(test_world ${GTEST_BOTH_LIBRARIES} pthread)

# 添加测试目标
add_test(NAME TestRigidBody COMMAND test_rigidbody)
add_test(NAME TestWorld COMMAND test_world)

# 打印GLEW和GLFW的路径信息
message(STATUS "GLEW include directory: /home/s5722414/local/usr/local/include")
message(STATUS "GLEW library directory: /home/s5722414/local/usr/local/lib64")
message(STATUS "GLFW include directory: /home/s5722414/glfw/include")
message(STATUS "GLFW library directory: /home/s5722414/glfw/build/src")
