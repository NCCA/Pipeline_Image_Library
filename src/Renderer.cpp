#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint loadShader(const char* vertexPath, const char* fragmentPath) {
    // Reading and compiling shader code
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

    // Compiling and linking shader programs
    // Error checking logic
    return 0; // Returns the shader program ID
}
