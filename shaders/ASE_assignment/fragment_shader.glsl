#version 330 core
in vec3 fragNormal;

out vec4 fragColor;

void main() {
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    float diff = max(dot(normalize(fragNormal), lightDir), 0.0);
    vec3 color = vec3(0.5, 0.5, 1.0) * diff + vec3(0.1); // Diffuse + Ambient Light
    fragColor = vec4(color, 1.0);
}
