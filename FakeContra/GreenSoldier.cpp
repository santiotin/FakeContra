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

	lastShoot = 0;
	shooting = false;
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

}

void GreenSoldier::update(int deltaTime, float posPlayerX, float posPlayerY, bool isDead)
{
	sprite->update(deltaTime);
	float posGreenSoldierX = getPosX();
	float posGreenSoldierY = getPosY();
	float distX = posGreenSoldierX - posPlayerX;
	if (distX < 65 && distX > -65) shooting = true;
	else if (distX > 64 && posGreenSoldierX > 230) {
		if(sprite->animation() != MOVE_LEFT)sprite->changeAnimation(MOVE_LEFT);
		posGreenSoldierX--;
		setPosition(glm::vec2(posGreenSoldierX, posGreenSoldierY));
		shooting = false;
	}
	else if (distX < -64 && posGreenSoldierX < 360) {
		if (sprite->animation() != MOVE_RIGHT)sprite->changeAnimation(MOVE_RIGHT);
		posGreenSoldierX++;
		setPosition(glm::vec2(posGreenSoldierX,posGreenSoldierY));
		shooting = false;
	}
	if (shooting || (posPlayerX < 231 && posGreenSoldierX < 235) || (posPlayerX > 359 && posGreenSoldierX > 355)) {
		sprite->changeAnimation(SHOOT);
		if (!isDead) doShoot(13.0, -65.0, distX * -0.006, 1.0, 2);
	}
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

glm::vec2 GreenSoldier::getPosition() {

	return glm::vec2(posGreenSoldier.x, posGreenSoldier.y);

}

glm::vec2 GreenSoldier::getBoxCollider() {

	return glm::vec2(32.0, 64.0);

}

glm::vec2 GreenSoldier::getStartP() {
	return glm::vec2(0.0, 0.0);
}

void GreenSoldier::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		glm::vec2 pos = glm::vec2(posGreenSoldier.x + desplX, posGreenSoldier.y + desplY);
		glm::vec2 dir = glm::vec2(dirX, dirY);
		BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
		lastShoot = Time::instance().getMili();
	}
	else {
		if (Time::instance().isAbleToShootEnemyLevel2(lastShoot)) {
			glm::vec2 pos = glm::vec2(posGreenSoldier.x + desplX, posGreenSoldier.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
}



