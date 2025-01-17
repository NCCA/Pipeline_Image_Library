#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "RigidBody.h"

class Renderer {
public:
    void render(const std::vector<std::unique_ptr<RigidBody>>& bodies);
};

#endif
