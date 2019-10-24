#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Turret1.h"
#include "Game.h"

#define PI 3.141592654




enum Turret1Anims
{
	POINT_1, POINT_2, POINT_3, POINT_4, POINT_5, POINT_6, POINT_7, POINT_8, POINT_9, POINT_10, POINT_11, POINT_12
};


void Turret::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Torreta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25, 0.33), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);

	lastShoot = 0;


	sprite->setAnimationSpeed(POINT_9, 8);
	sprite->addKeyframe(POINT_9, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(POINT_3, 8);
	sprite->addKeyframe(POINT_3, glm::vec2(0.25f, 0.00f));

	sprite->setAnimationSpeed(POINT_12, 8);
	sprite->addKeyframe(POINT_12, glm::vec2(0.50f, 0.00f));

	sprite->setAnimationSpeed(POINT_6, 8);
	sprite->addKeyframe(POINT_6, glm::vec2(0.75f, 0.00f));

	sprite->setAnimationSpeed(POINT_10, 8);
	sprite->addKeyframe(POINT_10, glm::vec2(0.00f, 0.33f));

	sprite->setAnimationSpeed(POINT_11, 8);
	sprite->addKeyframe(POINT_11, glm::vec2(0.25f, 0.33f));

	sprite->setAnimationSpeed(POINT_1, 8);
	sprite->addKeyframe(POINT_1, glm::vec2(0.50f, 0.33f));

	sprite->setAnimationSpeed(POINT_2, 8);
	sprite->addKeyframe(POINT_2, glm::vec2(0.75f, 0.33f));

	sprite->setAnimationSpeed(POINT_8, 8);
	sprite->addKeyframe(POINT_8, glm::vec2(0.00f, 0.66f));

	sprite->setAnimationSpeed(POINT_7, 8);
	sprite->addKeyframe(POINT_7, glm::vec2(0.25f, 0.66f));

	sprite->setAnimationSpeed(POINT_5, 8);
	sprite->addKeyframe(POINT_5, glm::vec2(0.50f, 0.66f));

	sprite->setAnimationSpeed(POINT_4, 8);
	sprite->addKeyframe(POINT_4, glm::vec2(0.75f, 0.66f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void Turret::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTurretX = getPosX();
	float posTurretY = getPosY();

	distX = posTurretX - posPlayerX;

	distY = posTurretY - posPlayerY;

	double alpha = atan2(distY, distX) - 0.15;
	cout << alpha << endl;
	if (alpha < 0.0f)
		alpha += 2 * PI;
	int valor = int(((6 * alpha) - (PI / 4)) / PI);

	if (valor == 0) sprite->changeAnimation(POINT_10);
	else if (valor == 1)sprite->changeAnimation(POINT_11);
	else if (valor == 2)sprite->changeAnimation(POINT_12);
	else if (valor == 3)sprite->changeAnimation(POINT_1);
	else if (valor == 4)sprite->changeAnimation(POINT_2);
	else if (valor == 5)sprite->changeAnimation(POINT_3);
	else if (valor == 6)sprite->changeAnimation(POINT_4);
	else if (valor == 7)sprite->changeAnimation(POINT_5);
	else if (valor == 8)sprite->changeAnimation(POINT_6);
	else if (valor == 9)sprite->changeAnimation(POINT_7);
	else if (valor == 10)sprite->changeAnimation(POINT_8);
	else if (valor == 11)sprite->changeAnimation(POINT_9);

	if (abs(distX) <= 320) {
		shootFromAnimation();
	}
}

void Turret::render()
{
	sprite->render();
}

void Turret::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Turret::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float Turret::getPosX()
{
	return float(posTurret.x);
}

float Turret::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 Turret::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 Turret::getBoxCollider() {

	return glm::vec2(60.0, 70.0);

}

void Turret::shootFromAnimation() {
	if (sprite->animation() == POINT_1) doShoot(45.0, -90.0, 1.0, -1.5, 6);
	if (sprite->animation() == POINT_2) doShoot(60.0, -73.0, 2.0, -1.0, 4);
	if (sprite->animation() == POINT_3) doShoot(65.0, -60.0, 1.0, 0.0, 6);

	if (sprite->animation() == POINT_4) doShoot(55.0, -45.0, 2.0, 1.0, 4);
	if (sprite->animation() == POINT_5) doShoot(40.0, -33.0, 1.0, 1.5, 6);
	if (sprite->animation() == POINT_6) doShoot(27.0, -30.0, 0.0, 1.0, 6);

	if (sprite->animation() == POINT_7) doShoot(10.0, -33.0, -1.0, 1.5, 6);
	if (sprite->animation() == POINT_8) doShoot(0.0, -45.0, -2.0, 1.0, 4);
	if (sprite->animation() == POINT_9) doShoot(0.0, -60.0, -1.0, 0.0, 6);

	if (sprite->animation() == POINT_10) doShoot(0.0, -75.0, -2.0, -1.0, 4);
	if (sprite->animation() == POINT_11) doShoot(10.0, -90.0, -1.0, -1.5, 6);
	if (sprite->animation() == POINT_12) doShoot(27.0, -90.0, 0.0, -1.0, 6);
}

void Turret::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
		glm::vec2 dir = glm::vec2(dirX, dirY);
		BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
		lastShoot = Time::instance().getMili();
	}
	else {
		if (Time::instance().isAbleToShootEnemy(lastShoot)) {
			glm::vec2 pos = glm::vec2(posTurret.x + desplX, posTurret.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
}