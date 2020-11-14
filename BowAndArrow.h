#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Shuriken.h"
#include "Transformations.h"

#include <utility>
#include <vector>
#include <time.h>
#include <stdlib.h>


#define INITIAL_PLAYER_X 5
#define INITIAL_PLAYER_Y 65
#define INITIAL_ARR_X 5
#define INITIAL_ARR_Y 65
#define PLAYER_MOVEMENT 150
#define STANDARD_LEN 100
#define BALLOON_DIAMETER 50
#define SHURIKEN_SPEED .1f
#define SHURIKEN_SCALE .3f
#define BALLOON_SPEED .08f
#define MAX_SPEED 1000
#define GRAVITY 9.8f
#define SHURIKEN_BONUS 500
#define SHURIKEN_DESTRUCT_SPEED .5f
#define BALLOON_BONUS 100
#define BALLOON_PENALTY 150
#define BALLOON_Y_SCALE 1.1f
#define BALLOON_X_SCALE .75f
#define BOW_X_SCALE .75f
#define BOW_Y_SCALE 1.25f

class BowAndArrow : public SimpleScene
{
public:
	BowAndArrow();
	~BowAndArrow();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

protected:
	glm::mat3 modelMatrix;
	float translateX, translateY;
	float scaleX, scaleY;
	float angularStep;
	float playerX, playerY;
	float arrX, arrY;
	int numShurikens, shuriIndex;
	int numReds, numYellows;
	std::vector<glm::vec3> shuris;
	std::vector<glm::vec2> reds;
	std::vector<glm::vec2> yellows;
	float currentSpeed;
	float arrowAngle;
	int releaseButton;
	int score;
	float launchAngle;
	int lives;
};
