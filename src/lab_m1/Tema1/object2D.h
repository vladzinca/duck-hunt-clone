#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    Mesh* CreateTriangle(const std::string& name, glm::vec3 corner1, glm::vec3 corner2, glm::vec3 corner3, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, float triangleCount, glm::vec3 color, bool fill);
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
}
