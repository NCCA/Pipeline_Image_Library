/****************************************************************************
* Copyright 2010 Evan Drumwright
 * This library is distributed under the terms of the Apache V2.0 License
 * (obtainable from http://www.apache.org/licenses/LICENSE-2.0).
 *
 * Modified version of the AABB class from the Moby library (Drumwright, 2010).
 * This code has been adapted to suit the specific needs of this project.
 ****************************************************************************/

#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>


struct Point3d {
    float x, y, z;
};

class AABB {
public:
    Point3d minp;
    Point3d maxp;

    AABB();
    AABB(const glm::vec3 &mn, const glm::vec3 &mx);

    static bool intersects(const AABB &a, const AABB &b);

    void print() const;
};

#endif
