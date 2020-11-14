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

	float length = STANDARD_LEN;
	float balloonDiameter = BALLOON_DIAMETER;

	playerX = INITIAL_PLAYER_X;
	playerY = INITIAL_PLAYER_Y;

	arrX = INITIAL_ARR_X;
	arrY = INITIAL_ARR_Y;

	numShurikens = 7 + rand() % 20;
	shuriIndex = 0;

	float scaleSize;

	for (int i = 0; i < numShurikens; ++i) {

		translateX = resolution.x + rand() % 20000;
		translateY = rand() % resolution.y;
		scaleSize = .3f;

		shuris.push_back(glm::vec3(translateX, translateY, scaleSize));
	}

	numReds = 15 + rand() % 20;

	Mesh* shuri = Shuriken::createShuriken("shuriken", corner, length, glm::vec3(.6f, 0, .3f));
	AddMeshToList(shuri);

	// 255, 102, 102
	Mesh* redCircle = Balloon::createCircle("redCircle", center, balloonDiameter, glm::vec3(1, .4f, .4f));
	AddMeshToList(redCircle);

	Mesh* redStringMesh = Balloon::createString("redString", center, balloonDiameter, glm::vec3(1, .4f, .4f));
	AddMeshToList(redStringMesh);

	// 255, 255, 102
	Mesh* yellowCircle = Balloon::createCircle("yellowCircle", center, balloonDiameter, glm::vec3(1, 1, .4f));
	AddMeshToList(yellowCircle);

	Mesh* yellowStringMesh = Balloon::createString("yellowString", center, balloonDiameter, glm::vec3(1, 1, .4f));
	AddMeshToList(yellowStringMesh);

	Mesh* bow = Player::createBow("bow", center, length, glm::vec3(.6f, 0, .3f));
	AddMeshToList(bow);

	Mesh* arrow = Player::createArrow("arrow", center, length, glm::vec3(1, 1, 1));
	AddMeshToList(arrow);
}


void BowAndArrow::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	// glClearColor(1, .5f, .5f, 1);
	// 255, 204, 229
	glClearColor(1, .8f, .91f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void BowAndArrow::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	{	 
		for (int i = 0; i < numShurikens; ++i) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformations::Translate(shuris[i].x, shuris[i].y);

			angularStep += .5f * deltaTimeSeconds;
			modelMatrix *= Transformations::Translate(100, 100);
			modelMatrix *= Transformations::Rotate(angularStep);
			modelMatrix *= Transformations::Scale(shuris[i].z, shuris[i].z);
			modelMatrix *= Transformations::Translate(-100, -100);

			shuris[i].x -= deltaTimeSeconds * SHURIKEN_SPEED * resolution.x;

			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
		}
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(250, 300);
		RenderMesh2D(meshes["redCircle"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["redString"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(250, 500);
		RenderMesh2D(meshes["yellowCircle"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["yellowString"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(playerX, playerY);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(arrX, arrY);
		
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
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->KeyHold(GLFW_KEY_W)) {
			playerY += deltaTime * 150;
			arrY += deltaTime * 150;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			playerY -= deltaTime * 150;
			arrY -= deltaTime * 150;
		}
	}
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