#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "TorBlue.h"
#include "Game.h"



enum TorBlueAnims
{
	SHOOT, DIE
};


void TorBlue::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/TorBlue.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	lastShoot = 0;

	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));

	shooting = false;
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void TorBlue::update(int deltaTime, float posPlayerX, float posPlayerY, bool isDead)
{
	sprite->update(deltaTime);
	float posTorBlueX = getPosX();
	float posTorBlueY = getPosY();
	float distX = posTorBlueX - posPlayerX;
	if (distX < 65 && distX > -65) shooting = true;
	else if (distX > 64 && posTorBlueX > 185) {
		posTorBlueX -= 2;
		setPosition(glm::vec2(posTorBlueX, posTorBlueY));
		shooting = false;
	}
	else if (distX < -64 && posTorBlueX < 400) {
		posTorBlueX += 2;
		setPosition(glm::vec2(posTorBlueX, posTorBlueY));
		shooting = false;
	}

	if (shooting) {
		
	}
	if(!isDead) doShoot(20.0, -50.0, distX * -0.004, 1.0, 4);

}

void TorBlue::render()
{
	sprite->render();
}

void TorBlue::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void TorBlue::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float TorBlue::getPosX()
{
	return float(posTurret.x);
}

float TorBlue::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 TorBlue::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 TorBlue::getBoxCollider() {

	return glm::vec2(64.0, 64.0);

}

glm::vec2 TorBlue::getStartP() {
	return glm::vec2(0.0, 0.0);
}

void TorBlue::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		int num = rand() % 153;
		if (num == 1) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 3);
			lastShoot = Time::instance().getMili();
		}
	}
	else {
		if (Time::instance().isAbleToShootEnemyLevel3(lastShoot)) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 3);
			lastShoot = Time::instance().getMili();
		}
	}
}




