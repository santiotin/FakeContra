#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "TorBoss.h"
#include "Game.h"



enum TorBossAnims
{
	SHOOT, DIE
};


void TorBoss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/TorBoss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(80, 68), glm::vec2(0.50, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.00f, 0.00f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void TorBoss::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTurretX = getPosX();
	float posTurretY = getPosY();

	distX = posTurretX - posPlayerX;

	distY = posTurretY - posPlayerY;


}

void TorBoss::render()
{
	sprite->render();
}

void TorBoss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void TorBoss::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float TorBoss::getPosX()
{
	return float(posTurret.x);
}

float TorBoss::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 TorBoss::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 TorBoss::getBoxCollider() {

	return glm::vec2(70.0, 55.0);

}

glm::vec2 TorBoss::getStartP() {
	return glm::vec2(0.0, 0.0);
}



