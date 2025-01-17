#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint loadShader(const char* vertexPath, const char* fragmentPath) {
    // 读取和编译着色器代码
    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath);

    if (!vShaderFile.is_open() || !fShaderFile.is_open()) {
        std::cerr << "Failed to open shader file(s)." << std::endl;
        return 0;
    }

    std::string vertexCode((std::istreambuf_iterator<char>(vShaderFile)), std::istreambuf_iterator<char>());
    std::string fragmentCode((std::istreambuf_iterator<char>(fShaderFile)), std::istreambuf_iterator<char>());

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // 编译和链接着色器程序
    // 错误检查逻辑
    return 0; // 返回着色器程序ID
}
