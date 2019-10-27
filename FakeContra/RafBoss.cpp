#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "RafBoss.h"
#include "Game.h"



enum RafBossAnims
{
	SHOOT, DIE
};


void RafBoss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/RafBoss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(80, 68), glm::vec2(0.50, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.00f, 0.00f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void RafBoss::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTurretX = getPosX();
	float posTurretY = getPosY();

	distX = posTurretX - posPlayerX;

	distY = posTurretY - posPlayerY;


}

void RafBoss::render()
{
	sprite->render();
}

void RafBoss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void RafBoss::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float RafBoss::getPosX()
{
	return float(posTurret.x);
}

float RafBoss::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 RafBoss::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 RafBoss::getBoxCollider() {

	return glm::vec2(70.0, 55.0);

}

glm::vec2 RafBoss::getStartP() {
	return glm::vec2(0.0, 0.0);
}



