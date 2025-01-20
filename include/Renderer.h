#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "RigidBody.h"
#include <ngl/Mat4.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void setViewMatrix(const ngl::Mat4 &viewMatrix);
    void setProjectionMatrix(const ngl::Mat4 &projectionMatrix);

    void render(const std::vector<std::unique_ptr<RigidBody>> &bodies);

private:
    ngl::Mat4 m_viewMatrix;
    ngl::Mat4 m_projectionMatrix;
};

#endif
