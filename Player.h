#pragma once

#include <Core/Engine.h>

namespace Player {
	Mesh *createBow(std::string name, glm::vec3 leftBottomCorner,
		float length, glm::vec3 color, bool fill = false, int numTriangles = 100);

	Mesh* createArrow(std::string name, glm::vec3 leftBottomCorner,
		float length, glm::vec3 color, bool fill = true);
}