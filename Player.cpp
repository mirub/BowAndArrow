#include "Player.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

Mesh* Player::createBow(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color, bool fill, int numTriangles) {

	glm::vec3 center = leftBottomCorner;
	float BalloonRadius = 0.5f;

	float standardScaleOX = .75f;
	float standardScaleOY = 1.25f;

	std::vector<VertexFormat> vertices;

	Mesh* bow = new Mesh(name);

	std::vector<unsigned short> indices;

	// Draw the circle
	for (GLushort i = 0; i <= numTriangles; ++i)
	{
		float arg = 1.0f * (GLfloat)M_PI * i / numTriangles;

		vertices.push_back(
			VertexFormat(center + glm::vec3(standardScaleOX * length * sin(arg) * BalloonRadius,
				length * cos(arg) * BalloonRadius * standardScaleOY, 0), color));
		indices.push_back(i);
	}

	indices.push_back(numTriangles);
	indices.push_back(1);

	bow->SetDrawMode(GL_LINE_LOOP);

	bow->InitFromData(vertices, indices);
	return bow;
}

Mesh* Player::createArrow(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color, bool fill) {

	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices = {
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0.1 * length, -.2f * length, 0), color),
		VertexFormat(corner + glm::vec3(-0.1 * length, -.2f * length, 0), color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color)
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 0, 3};

	Mesh* arrow = new Mesh(name);
	arrow->SetDrawMode(GL_LINE_STRIP);

	arrow->InitFromData(vertices, indices);
	return arrow;
}