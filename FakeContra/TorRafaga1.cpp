#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "TorRafaga1.h"
#include "Scene.h"
#include "Game.h"


#define PI 3.141592654


enum TorRafagaAnims
{
	POINT_9, POINT_10, POINT_11
};


void TorRafaga::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/TorRafaga.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.33, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	lastShoot = 0;



	sprite->setAnimationSpeed(POINT_9, 8);
	sprite->addKeyframe(POINT_9, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(POINT_10, 8);
	sprite->addKeyframe(POINT_10, glm::vec2(0.33f, 0.00f));

	sprite->setAnimationSpeed(POINT_11, 8);
	sprite->addKeyframe(POINT_11, glm::vec2(0.66f, 0.00f));



	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void TorRafaga::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTorRafX = getPosX();
	float posTorRafY = getPosY();

	distX = posTorRafX - posPlayerX;

	distY = posTorRafY - posPlayerY;

	double alpha = atan2(distY, distX) - 0.25;
	cout << alpha << endl;
	if (alpha < 0.0f)
		alpha += 2 * PI;
	int valor = int(((6 * alpha) - (PI / 4)) / PI);

	if (valor == 11) sprite->changeAnimation(POINT_9);
	else if (valor == 0)sprite->changeAnimation(POINT_10);
	else if (valor == 1)sprite->changeAnimation(POINT_11);

	if (abs(distX) <= 320) {
		shootFromAnimation();
	}
	
}

void TorRafaga::render()
{
	sprite->render();
}

void TorRafaga::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void TorRafaga::setPosition(const glm::vec2& pos)
{
	posTorRafaga = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTorRafaga.x), float(tileMapDispl.y + posTorRafaga.y)));
}

float TorRafaga::getPosX()
{
	return float(posTorRafaga.x);
}

float TorRafaga::getPosY()
{
	return float(posTorRafaga.y);
}

glm::vec2 TorRafaga::getPosition() {
	return glm::vec2(posTorRafaga.x, posTorRafaga.y);
}

glm::vec2 TorRafaga::getBoxCollider() {

	return glm::vec2(60.0, 90.0);

}

void TorRafaga::shootFromAnimation() {
	if (sprite->animation() == POINT_9) doShoot(0.0, -60.0, -1.0, 0.0, 6);
	if (sprite->animation() == POINT_10) doShoot(0.0, -75.0, -2.0, -1.0, 4);
	if (sprite->animation() == POINT_11) doShoot(20.0, -80.0, -1.0, -1.5, 6);
}

void TorRafaga::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		glm::vec2 pos = glm::vec2(posTorRafaga.x + desplX, posTorRafaga.y + desplY);
		glm::vec2 dir = glm::vec2(dirX, dirY);
		BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
		lastShoot = Time::instance().getMili();
	}
	else {
		if (Time::instance().isAbleToShootEnemy(lastShoot)) {
			glm::vec2 pos = glm::vec2(posTorRafaga.x + desplX, posTorRafaga.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createEnemyBullet(pos, dir, speed, 0);
			lastShoot = Time::instance().getMili();
		}
	}
}

