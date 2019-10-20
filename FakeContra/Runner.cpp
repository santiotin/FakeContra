#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Runner.h"
#include "Scene.h"
#include "Game.h"


#define WALK_STEP 1.5;
#define FALL_STEP 4

enum RunnerAnims
{
	MOVE_LEFT_NS
};


void Runner::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Runner.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	
	sprite->setAnimationSpeed(MOVE_LEFT_NS, 8);
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.00f, 0.00f));
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.25f, 0.00f));
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.50f, 0.00f));
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.75f, 0.00f));
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.00f, 0.50f));
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.25f, 0.50f));
	sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.50f, 0.50f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void Runner::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posRunnerX = getPosX();
	float posRunnerY = getPosY();

	distX = posRunnerX - posPlayerX;

	distY = posRunnerY - posPlayerY;
	if (posRunnerY <= 7) sprite->changeAnimation(MOVE_LEFT_NS);
	posRunner.x -= WALK_STEP;
	if (posRunner.x < 25)posRunner.y += FALL_STEP;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posRunner.x), float(tileMapDispl.y + posRunner.y)));
}

void Runner::render()
{
	sprite->render();
}

void Runner::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Runner::setPosition(const glm::vec2& pos)
{
	posRunner = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posRunner.x), float(tileMapDispl.y + posRunner.y)));
}

float Runner::getPosX()
{
	return float(posRunner.x);
}

float Runner::getPosY()
{
	return float(posRunner.y);
}




