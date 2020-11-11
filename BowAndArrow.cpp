#include "BowAndArrow.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

BowAndArrow::BowAndArrow()
{
}

BowAndArrow::~BowAndArrow()
{
}

void BowAndArrow::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;		// logic x
	logicSpace.y = 0;		// logic y
	logicSpace.width = 4;	// logic width
	logicSpace.height = 4;	// logic height

	glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
	length = 0.99f;

	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0));
	//AddMeshToList(square1);

}

void BowAndArrow::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void BowAndArrow::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations

	// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D

	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
}

void BowAndArrow::FrameEnd()
{

}

void BowAndArrow::OnInputUpdate(float deltaTime, int mods)
{

}

void BowAndArrow::OnKeyPress(int key, int mods)
{
	// add key press event
}

void BowAndArrow::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void BowAndArrow::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void BowAndArrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void BowAndArrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void BowAndArrow::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void BowAndArrow::OnWindowResize(int width, int height)
{
}
