#include "Balloon.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

Mesh* Balloon::createCircle(std::string name, glm::vec3 circleCenter, 
	float length, glm::vec3 color, bool fill, int numTriangles) {
	
	glm::vec3 center = circleCenter;
	float BalloonRadius = 0.8f;
	float standardScaleOX = .75f;
	float standardScaleOY = 1.1f;

	std::vector<VertexFormat> vertices;

	Mesh* circle = new Mesh(name);

	std::vector<unsigned short> indices;

	// Draw the circle
	for (GLushort i = 0; i <= numTriangles; ++i)
	{
		float arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

		vertices.push_back(
			VertexFormat(center + glm::vec3(standardScaleOX * length * cos(arg) * BalloonRadius,
				length * sin(arg) * BalloonRadius * standardScaleOY, 0), color));
		indices.push_back(i);
	}

	indices.push_back(numTriangles);
	indices.push_back(1);

	// Add bottom triangle

	circle->SetDrawMode(GL_TRIANGLE_FAN);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Balloon::createString(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color, bool fill) {

	glm::vec3 corner = leftBottomCorner;

	length *= 2;
		
	std::vector<VertexFormat> vertices = {
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0.1 * length, -.2f * length, 0), color),
		VertexFormat(corner + glm::vec3(-0.1 * length, -.3f * length, 0), color),
		VertexFormat(corner + glm::vec3(0.1 * length, -.4f * length, 0), color),
		VertexFormat(corner + glm::vec3(-0.1 * length, -.5f * length, 0), color),
		VertexFormat(corner + glm::vec3(0.1 * length, -.6f * length, 0), color),
		VertexFormat(corner + glm::vec3(-0.1 * length, -.7f * length, 0), color),
		VertexFormat(corner + glm::vec3(0.1 * length, -.8f * length, 0), color),
		VertexFormat(corner + glm::vec3(-0.1 * length, -.9f * length, 0), color)
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	Mesh* stringMesh = new Mesh(name);
	stringMesh->SetDrawMode(GL_LINE_STRIP);

	stringMesh->InitFromData(vertices, indices);
	return stringMesh;
}
