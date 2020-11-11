#pragma once

#include <Core/Engine.h>

namespace Player {
	Mesh *createPlayer(std::string name, glm::vec3 leftBottomCorner,
		float length, glm::vec3 color, bool fill = false);
}