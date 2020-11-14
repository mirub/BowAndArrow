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

	numShurikens = 100 + rand() % 20;
	shuriIndex = 0;
	releaseButton = 0;
	score = 0;
	lives = 3;

	float scaleSize;

	currentSpeed = 5;

	for(int i = 0; i < numShurikens; ++i) {

		if (i != 0) {
			translateX = resolution.x + rand() % 10000000 + .05f * shuris[i - (short)1].x;
		}
		translateY = rand() % resolution.y;
		scaleSize = SHURIKEN_SCALE;

		shuris.push_back(glm::vec3(translateX, translateY, scaleSize));
	}

	numReds = 100 + rand() % 20;

	for (int i = 0; i < numReds; ++i) {

		translateX = rand() % resolution.x + 100;
		if (i != 0) {
			translateY = -rand() % 500000000 - .5f * reds[i - (short)1].y;
		}

		reds.push_back(glm::vec2(translateX, translateY));
	}

	numYellows = 150 + rand() % 20;

	for (int i = 0; i < numYellows; ++i) {

		translateX = rand() % resolution.x + 100;
		if (i != 0) {
			translateY = -rand() % 700000000 - .5f * yellows[i - (short)1].y;
		}

		yellows.push_back(glm::vec2(translateX, translateY));
	}


	Mesh* shuri = Shuriken::createShuriken("shuriken", corner, length, glm::vec3(.6f, 0, .3f));
	AddMeshToList(shuri);

	Mesh* redCircle = Balloon::createCircle("redCircle", center, balloonDiameter, glm::vec3(1, .4f, .4f));
	AddMeshToList(redCircle);

	Mesh* redStringMesh = Balloon::createString("redString", center, balloonDiameter, glm::vec3(1, .4f, .4f));
	AddMeshToList(redStringMesh);

	Mesh* yellowCircle = Balloon::createCircle("yellowCircle", center, balloonDiameter, glm::vec3(1, 1, .4f));
	AddMeshToList(yellowCircle);

	Mesh* yellowStringMesh = Balloon::createString("yellowString", center, balloonDiameter, glm::vec3(1, 1, .4f));
	AddMeshToList(yellowStringMesh);

	Mesh* bow = Player::createBow("bow", center, length, glm::vec3(.6f, 0, .3f));
	AddMeshToList(bow);

	Mesh* arrow = Player::createArrow("arrow", center, length, glm::vec3(.6f, 0, .3f));
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

			angularStep += .07f * deltaTimeSeconds;
			modelMatrix *= Transformations::Translate(100, 100);
			modelMatrix *= Transformations::Rotate(angularStep * .75f);
			modelMatrix *= Transformations::Scale(shuris[i].z, shuris[i].z);
			modelMatrix *= Transformations::Translate(-100, -100);

			shuris[i].x -= deltaTimeSeconds * SHURIKEN_SPEED * resolution.x;

			// Arrow collision
			float shuriDiameter = sqrt((STANDARD_LEN * 2 * shuris[i].z)
				* (STANDARD_LEN * 2 * shuris[i].z) * 2);
			float shuriCenterX = shuris[i].x + (shuriDiameter / 2);
			float shuriCenterY = shuris[i].y + (shuriDiameter / 2);
			float distanceX = fabs(arrX - shuriCenterX);
			float distanceY = fabs(arrY - shuriCenterY);

			if (distanceX < (shuriDiameter / 2) && distanceY < (shuriDiameter / 2)) {
				// is collision
				score += SHURIKEN_BONUS;
				//cout << score << "\n";
				shuris[i].x = -200;
			}

			// Bow collison -- NOT WORKING YET
			//float bowDiameterX = BALLOON_DIAMETER * BOW_X_SCALE;
			//float bowDiameterY = BALLOON_DIAMETER * BOW_Y_SCALE;

			float bowDistanceX = fabs(playerX - shuriCenterX);
			float bowDistanceY = fabs(playerY - shuriCenterY);
			float distance = sqrt(bowDistanceX * bowDistanceX +
				bowDistanceY * bowDistanceY);

			
			if (distance < (BALLOON_DIAMETER + shuriDiameter)) {
				shuris[i].x = resolution.x - (BALLOON_DIAMETER + shuriDiameter);
				shuris[i].y = resolution.y + (BALLOON_DIAMETER + shuriDiameter);
				lives--;
			}
			
			
			// Game Over
			if (lives == 0) {
				cout << "GAME OVER\n";
				exit(0);
			}
			

			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
		}
	}

	{	
		for (int i = 0; i < numReds; ++i) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformations::Translate(reds[i].x, reds[i].y);

			reds[i].y += deltaTimeSeconds * BALLOON_SPEED * resolution.y;

			float balloonDiameterY = STANDARD_LEN * BALLOON_Y_SCALE;
			float balloonDiameterX = STANDARD_LEN * BALLOON_X_SCALE;
			float distanceX = fabs(arrX - reds[i].x);
			float distanceY = fabs(arrY - reds[i].y);

			if (distanceX < (balloonDiameterX / 2) && distanceY < (balloonDiameterY / 2)) {
				// is collision
				score += BALLOON_BONUS;
				//cout << score << "\n";
				reds[i].y = resolution.y + 100;
			}

			RenderMesh2D(meshes["redCircle"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["redString"], shaders["VertexColor"], modelMatrix);
		}
	}

	{
		for (int i = 0; i < numYellows; ++i) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformations::Translate(yellows[i].x, yellows[i].y);

			yellows[i].y += deltaTimeSeconds * BALLOON_SPEED * resolution.y;

			float balloonDiameterY = STANDARD_LEN * BALLOON_Y_SCALE;
			float balloonDiameterX = STANDARD_LEN * BALLOON_X_SCALE;
			float distanceX = fabs(arrX - yellows[i].x);
			float distanceY = fabs(arrY - yellows[i].y);

			if (distanceX < (balloonDiameterX / 2) && distanceY < (balloonDiameterY / 2)) {
				// is collision
				score -= BALLOON_PENALTY;
				//cout << score << "\n";
				yellows[i].y = resolution.y + 100;
			}
			
			RenderMesh2D(meshes["yellowCircle"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["yellowString"], shaders["VertexColor"], modelMatrix);
		}
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(playerX, playerY);
		float radians = arrowAngle;
		modelMatrix *= Transformations::Rotate(radians);

		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(arrX, arrY);

		// Release the arrow
		if (releaseButton) {
			arrX += currentSpeed * deltaTimeSeconds * cos(launchAngle);

			arrY += currentSpeed * deltaTimeSeconds * sin(launchAngle) - 
				(GRAVITY * deltaTimeSeconds * deltaTimeSeconds / 2);

			float radians = 270 * (M_PI / 180) + launchAngle;
			modelMatrix *= Transformations::Rotate(radians);

			if (arrX > resolution.x || arrY > resolution.y || arrY < 0) {
				//cout << playerX << " " << playerY << "\n";
				arrX = playerX;
				arrY = playerY;
				releaseButton = 0;
			}
		}

		// Rotate with bow
		if (!releaseButton) {
			arrX = playerX;
			arrY = playerY;
			float radians = 270 * (M_PI / 180) + arrowAngle;
			modelMatrix *= Transformations::Rotate(radians);
		}

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
			if (!releaseButton) {
				arrY += deltaTime * 150;
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			playerY -= deltaTime * 150;
			if (!releaseButton) {
				arrY -= deltaTime * 150;
			}
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		//cout << playerX << " " << playerY << "\n";
		arrX = playerX;
		arrY = playerY;

		if (window->KeyHold(GLFW_KEY_W)) {
			playerY += deltaTime * 150;
			if (!releaseButton) {
				arrY += deltaTime * 150;
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			playerY -= deltaTime * 150;
			if (!releaseButton) {
				arrY -= deltaTime * 150;
			}
		}

		currentSpeed += deltaTime * 100;

		if (currentSpeed == MAX_SPEED) {
			currentSpeed = 0;
		}

		releaseButton = 0;
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
	glm::ivec2 resolution = window->GetResolution();
	arrowAngle = atan((double) (resolution.y - mouseY - arrY) / mouseX);
}

void BowAndArrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void BowAndArrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	glm::ivec2 resolution = window->GetResolution();

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		launchAngle = arrowAngle;
		releaseButton = 1;
	}
}

void BowAndArrow::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}