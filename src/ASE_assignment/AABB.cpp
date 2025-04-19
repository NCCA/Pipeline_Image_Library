/****************************************************************************
* Copyright 2010 Evan Drumwright
 * This library is distributed under the terms of the Apache V2.0 License
 * (obtainable from http://www.apache.org/licenses/LICENSE-2.0).
 *
 * This code has been adapted from Moby library (Drumwright, 2010) for the
 * specific needs of the project. Modifications have been made to suit the
 * project requirements.
 ****************************************************************************/

#include "AABB.h"
#include <iostream>

// Modified version of the AABB class from Moby library (Drumwright, 2010)
// The original code has been adapted to include additional methods specific to the project.

/// @brief AABB default constructor
/// Modified from :-
/// Drumwright, E. (2010). Moby library. [online]. [Accessed 2025]. Available from: "http://www.examplelink.com".
AABB::AABB() {
    minp = {0.f, 0.f, 0.f};
    maxp = {0.f, 0.f, 0.f};
}

/// @brief AABB constructor with min and max values
/// @param mn The minimum point (xmin, ymin, zmin)
/// @param mx The maximum point (xmax, ymax, zmax)
AABB::AABB(const glm::vec3 &mn, const glm::vec3 &mx) {
    minp = {mn.x, mn.y, mn.z};
    maxp = {mx.x, mx.y, mx.z};
}

/// @brief Checks if two AABBs intersect
/// @param a The first AABB
/// @param b The second AABB
/// @return Returns true if the AABBs intersect, false otherwise
bool AABB::intersects(const AABB &a, const AABB &b) {
    return (a.minp.x <= b.maxp.x && a.maxp.x >= b.minp.x) &&
           (a.minp.y <= b.maxp.y && a.maxp.y >= b.minp.y) &&
           (a.minp.z <= b.maxp.z && a.maxp.z >= b.minp.z);
}

/// @brief Prints the min and max coordinates of the AABB
void AABB::print() const {
    std::cout << "AABB: min(" << minp.x << ", "
              << minp.y << ", " << minp.z
              << ") max(" << maxp.x << ", "
              << maxp.y << ", " << maxp.z
              << ")\n";
}
