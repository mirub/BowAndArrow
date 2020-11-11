#include "Shuriken.h"

Shuriken::Shuriken() {
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1, 1), glm::vec3(0, 1, 1)), //0
			// TODO: Complete the information for the cube
			VertexFormat(glm::vec3(1, -1, 1), glm::vec3(0, 1, 1)),  //1
			VertexFormat(glm::vec3(-1, -1, 3), glm::vec3(0, 1, 1)), //2
			VertexFormat(glm::vec3(1, -1, 3), glm::vec3(0, 1, 1)),  //3
			VertexFormat(glm::vec3(-1, 1, 1), glm::vec3(0, 1, 1)),  //4
			VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1)),   //5
			VertexFormat(glm::vec3(-1, 1, 3), glm::vec3(0, 1, 1)),  //6
			VertexFormat(glm::vec3(1, 1, 3), glm::vec3(0, 1, 1))    //7
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			1, 3, 2,	// indices for second triangle
			5, 1, 7,
			1, 3, 7,
			7, 3, 2,
			2, 6, 7,
			4, 5, 6,
			5, 7, 6,
			6, 2, 0,
			4, 6, 0,
			4, 1, 5,
			4, 0, 1
			// TODO: Complete indices data
		};

		meshes["cube1"] = new Mesh("generated cube 1");
		meshes["cube1"]->InitFromData(vertices, indices);

		// Create a new mesh from buffer data
		Mesh* cube = CreateMesh("cube3", vertices, indices);
	}
}

Shuriken::~Shuriken()
{

}

Mesh* Shuriken::createShuriken(const char* name, const std::vector<VertexFormat>& vertices,
	const std::vector<unsigned short>& indices) {

	unsigned int VAO = 0;

	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// TODO: Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	Mesh* shuriken = new Mesh(name);
	shuriken->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return shuriken;
}