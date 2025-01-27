#include "Ground.h"

Ground::Ground(const glm::vec3 &pos, const glm::vec3 &sz)
    : position(pos), size(sz)
{

    aabb.minp = { pos.x - sz.x*0.5f,
                  pos.y,
                  pos.z - sz.z*0.5f };

    aabb.maxp = { pos.x + sz.x*0.5f,
                  pos.y + sz.y,
                  pos.z + sz.z*0.5f };

}
