#include "BowAndArrow.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Shuriken.h"
#include "Balloon.h"
#include "Player.h"

using namespace std;

BowAndArrow::BowAndArrow()
{
}

BowAndArrow::~BowAndArrow()
{
}

void BowAndArrow::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 center = glm::vec3(0, 0, 0);
	float length = 100;
	float balloonDiameter = 50;

	Mesh* shuri = Shuriken::createShuriken("shuriken", corner, length, glm::vec3(1, 0, 0));
	AddMeshToList(shuri);

	Mesh* circle = Balloon::createCircle("circle", center, balloonDiameter, glm::vec3(1, 0, 1));
	AddMeshToList(circle);

	Mesh* stringMesh = Balloon::createString("string", center, balloonDiameter, glm::vec3(1, 0, 1));
	AddMeshToList(stringMesh);

	Mesh* bow = Player::createBow("bow", center, length, glm::vec3(1, 1, 1));
	AddMeshToList(bow);

	Mesh* arrow = Player::createArrow("arrow", center, length, glm::vec3(1, 1, 1));
	AddMeshToList(arrow);
}


void BowAndArrow::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	// glClearColor(1, .5f, .5f, 1);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void BowAndArrow::Update(float deltaTimeSeconds)
{
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(150, 250);

		//modelMatrix *= Transformations::Translate(100, 100);
		//modelMatrix *= Transformations::Scale(.15f, .15f);

		float scaledWidth = (.15f * 200) / 2;

		angularStep += 1.5f * deltaTimeSeconds;
		modelMatrix *= Transformations::Translate(100, 100);
		modelMatrix *= Transformations::Rotate(angularStep);
		modelMatrix *= Transformations::Scale(.15f, .15f);
		modelMatrix *= Transformations::Translate(-100, -100);
		
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(250, 300);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["string"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(5, 65);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(100, 85);
		
		float radians = 285 * (M_PI / 180);
		modelMatrix *= Transformations::Rotate(radians);

		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	}
}

void BowAndArrow::FrameEnd()
{

}

void BowAndArrow::OnInputUpdate(float deltaTime, int mods)
{

}

void BowAndArrow::OnKeyPress(int key, int mods)
{

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