#include "SpeedBar.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>

Mesh* SpeedBar::createSpeedBar(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color, bool fill) {

	glLineWidth(2);
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{	
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
	};

	Mesh* speedBar = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	speedBar->SetDrawMode(GL_LINE_STRIP);

	speedBar->InitFromData(vertices, indices);
	return speedBar;

}