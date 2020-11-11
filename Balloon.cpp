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

Mesh* createString(std::string name, glm::vec3 leftBottomCorner,
	float length, glm::vec3 color, bool fill) {
		
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	glm::vec3 center = leftBottomCorner;


}
