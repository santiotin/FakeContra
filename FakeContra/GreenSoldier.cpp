#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "GreenSoldier.h"
#include "Scene.h"
#include "Game.h"
#include "BulletManager.h"


#define PI 3.141592654
#define SPEED 6

enum GreenSoldierAnims
{
	MOVE_LEFT,MOVE_RIGHT, SHOOT
};


void GreenSoldier::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/GreenSoldier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.33, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
		
	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00, 0.00f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.33f, 0.00f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.66f, 0.00f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.00f, 0.50f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.33f, 0.50f));

	shooting = false;
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

}

void GreenSoldier::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posGreenSoldierX = getPosX();
	float posGreenSoldierY = getPosY();
	float distX = posGreenSoldierX - posPlayerX;
	if (distX < 64 && distX > -64) shooting = true;
	else if (distX > 64) {
		if(sprite->animation() != MOVE_LEFT)sprite->changeAnimation(MOVE_LEFT);
		shooting = false;
	}
	else if (distX < -64) {
		if (sprite->animation() != MOVE_RIGHT)sprite->changeAnimation(MOVE_RIGHT);
		shooting = false;
	}
	if (shooting) sprite->changeAnimation(SHOOT);
}

void GreenSoldier::render()
{
	sprite->render();
}

void GreenSoldier::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void GreenSoldier::setPosition(const glm::vec2& pos)
{
	posGreenSoldier = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGreenSoldier.x), float(tileMapDispl.y + posGreenSoldier.y)));
}

float GreenSoldier::getPosX()
{
	return float(posGreenSoldier.x);
}

float GreenSoldier::getPosY()
{
	return float(posGreenSoldier.y);
}




