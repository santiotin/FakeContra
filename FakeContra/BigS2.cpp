#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BigS2.h"
#include "Game.h"



enum BigS2Anims
{
	SHOOT
};


void BigS2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	game_over = false;
	lastShoot = 0;
	spritesheet.loadFromFile("images/BBS2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(42, 42), glm::vec2(0.33, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);


	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.33f, 0.00f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.66f, 0.00f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void BigS2::update(int deltaTime, float posPlayerX, float posPlayerY, bool isDead)
{
	sprite->update(deltaTime);
	float posTurretX = getPosX();
	float posTurretY = getPosY();

	distX = posTurretX - posPlayerX;

	distY = posTurretY - posPlayerY;

	if (!isDead) doShoot(13.0, -65.0, distX * -0.006, 1.0, 2);

}

void BigS2::render()
{
	sprite->render();
}

void BigS2::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BigS2::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float BigS2::getPosX()
{
	return float(posTurret.x);
}

float BigS2::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 BigS2::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 BigS2::getBoxCollider() {

	return glm::vec2(32.0, 32.0);

}

glm::vec2 BigS2::getStartP() {
	return glm::vec2(0.0, 0.0);
}

void BigS2::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		int num = rand() % 153;
		if (num == 7) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			if (!game_over) sndPlaySound(TEXT("musica/level01-turret-shoot.wav"), SND_ASYNC);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
	else {
		if (Time::instance().isAbleToShootEnemyLevel2(lastShoot)) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			if (!game_over) sndPlaySound(TEXT("musica/level01-turret-shoot.wav"), SND_ASYNC);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
}


