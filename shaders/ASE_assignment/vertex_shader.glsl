#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 MVP;

out vec3 fragNormal;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    fragNormal = normal;
}
