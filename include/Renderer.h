#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "RigidBody.h"

// Function declaration to generate random colors
glm::vec3 generateRandomColor();

class Renderer {
public:
    // Constructor and Destructor
    Renderer();
    ~Renderer();

    // Render function with three parameters (used for bodies rendering)
    void render(const std::vector<std::unique_ptr<RigidBody>>& bodies,
                const glm::mat4& view,
                const glm::mat4& projection);

    // Render function with four parameters (used for bodies and ground rendering)
    void render(const std::vector<std::unique_ptr<RigidBody>>& bodies,
                const glm::mat4& view,
                const glm::mat4& projection,
                float groundTop);

    // Function to render the ground
    void renderGround(float groundY, float halfSize,
                      const glm::mat4& view,
                      const glm::mat4& projection);
};

#endif // RENDERER_H_
