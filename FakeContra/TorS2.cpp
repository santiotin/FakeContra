#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "TorS2.h"
#include "Game.h"



enum TorS2Anims
{
	SHOOT
};


void TorS2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/TorS2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);

	lastShoot = 0;


	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.33f, 0.00f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.66f, 0.00f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void TorS2::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTurretX = getPosX();
	float posTurretY = getPosY();

	distX = posTurretX - posPlayerX;

	distY = posTurretY - posPlayerY;

	doShoot(13.0, -65.0, distX * -0.006, 1.0, 2);


}

void TorS2::render()
{
	sprite->render();
}

void TorS2::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void TorS2::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float TorS2::getPosX()
{
	return float(posTurret.x);
}

float TorS2::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 TorS2::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 TorS2::getBoxCollider() {

	return glm::vec2(32.0, 32.0);

}

glm::vec2 TorS2::getStartP() {
	return glm::vec2(0.0, 0.0);
}

void TorS2::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		int num = rand() % 153;
		if (num == 7) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
	else {
		if (Time::instance().isAbleToShootEnemyLevel2(lastShoot)) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
}




