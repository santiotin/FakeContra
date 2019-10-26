#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BolS2.h"
#include "Game.h"

#define PI 3.141592654




enum BolS2Anims
{
	SHOOT
};


void BolS2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/BolS2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);


	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.33f, 0.00f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.66f, 0.00f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void BolS2::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTurretX = getPosX();
	float posTurretY = getPosY();

	distX = posTurretX - posPlayerX;

	distY = posTurretY - posPlayerY;


}

void BolS2::render()
{
	sprite->render();
}

void BolS2::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BolS2::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float BolS2::getPosX()
{
	return float(posTurret.x);
}

float BolS2::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 BolS2::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 BolS2::getBoxCollider() {

	return glm::vec2(32.0, 32.0);

}

glm::vec2 BolS2::getStartP() {
	return glm::vec2(0.0, 0.0);
}




