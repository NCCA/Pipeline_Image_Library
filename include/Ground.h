#ifndef GROUND_H_
#define GROUND_H_

#include <glm/glm.hpp>
#include "AABB.h"

class Ground {
public:
    AABB aabb;          // AABB indicates the ground
    glm::vec3 position; // centre of the ground
    glm::vec3 size;     // size of the ground

    Ground(const glm::vec3 &pos, const glm::vec3 &sz);
};

#endif // GROUND_H_
