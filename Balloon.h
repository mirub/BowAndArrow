#pragma once

#include <Core/Engine.h>

namespace Balloon {
	Mesh* createCircle(std::string name, glm::vec3 leftBottomCorner,
		float length, glm::vec3 color, bool fill = true, int numTriangles = 180);

	Mesh* createString(std::string name, glm::vec3 leftBottomCorner,
		float length, glm::vec3 color, bool fill = true);
}