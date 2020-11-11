#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

namespace Shuriken
{

	Mesh* createShuriken(std::string name, glm::vec3 leftBottomCorner,
			float length, glm::vec3 color, bool fill = false);
};