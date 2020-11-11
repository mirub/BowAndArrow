#include "Shuriken.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

Mesh* Shuriken::createShuriken(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color, bool fill = false){

	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(length, length, 0), color), // center (0)
		VertexFormat(corner, color), // bottom left (1)
		VertexFormat(corner + glm::vec3(0, length, 0), color), // bottom left right angle (2) 
		VertexFormat(corner + glm::vec3(0,  2 * length, 0), color), // top triangle left (3)
		VertexFormat(corner + glm::vec3(length,  2 * length, 0), color), // top triangle right (4)
		VertexFormat(corner + glm::vec3(2 * length,  2 * length, 0), color), // right triangle up (5)
		VertexFormat(corner + glm::vec3(2 * length, length, 0), color), // right triangle down (6)
		VertexFormat(corner + glm::vec3(2 * length, 0, 0), color), // bottom right (7)
		VertexFormat(corner + glm::vec3(length, 0 , 0), color) // bottom middle (8)
	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	if (!fill) {
		shuriken->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(2);
		indices.push_back(4);
		indices.push_back(6);
		indices.push_back(8);
	}

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}