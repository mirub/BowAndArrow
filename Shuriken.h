#pragma once

#include <Core/Engine.h>

class Shuriken
{
public:
	Shuriken();
	~Shuriken();

	Mesh* createShuriken(const char* name, const std::vector<VertexFormat>& vertices,
							const std::vector<unsigned short>& indices);

private:
	
};