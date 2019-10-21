#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Soldier.h"
#include "Scene.h"
#include "Game.h"


#define PI 3.141592654


enum SoldierAnims
{
	POINT_9L, POINT_105L, POINT_75L, POINT_9R, POINT_105R, POINT_75R
};


void Soldier::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Soldier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 96), glm::vec2(0.33, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);


	sprite->setAnimationSpeed(POINT_9L, 8);
	sprite->addKeyframe(POINT_9L, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(POINT_105L, 8);
	sprite->addKeyframe(POINT_105L, glm::vec2(0.33f, 0.00f));

	sprite->setAnimationSpeed(POINT_75L, 8);
	sprite->addKeyframe(POINT_75L, glm::vec2(0.66f, 0.00f));

	sprite->setAnimationSpeed(POINT_9R, 8);
	sprite->addKeyframe(POINT_9R, glm::vec2(0.00f, 0.50f));

	sprite->setAnimationSpeed(POINT_105R, 8);
	sprite->addKeyframe(POINT_105R, glm::vec2(0.33f, 0.50f));

	sprite->setAnimationSpeed(POINT_75R, 8);
	sprite->addKeyframe(POINT_75R, glm::vec2(0.66f, 0.50f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void Soldier::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posSoldierX = getPosX();
	float posSoldierY = getPosY();

	distX = posSoldierX - posPlayerX;

	distY = posSoldierY - posPlayerY;

	double alpha = atan2(distY, distX) - 0;
	cout << alpha << endl;
	if (alpha < 0.0f)
		alpha += 2 * PI;
	int valor = int(((6 * alpha) - (PI / 4)) / PI);

	if (valor == 0) sprite->changeAnimation(POINT_9L);
	else if (valor == 1)sprite->changeAnimation(POINT_105L);
	else if (valor == 2)sprite->changeAnimation(POINT_105L);
	else if (valor == 3)sprite->changeAnimation(POINT_105R);
	else if (valor == 4)sprite->changeAnimation(POINT_105R);
	else if (valor == 5)sprite->changeAnimation(POINT_9R);
	else if (valor == 6)sprite->changeAnimation(POINT_9R);
	else if (valor == 7)sprite->changeAnimation(POINT_75R);
	else if (valor == 8)sprite->changeAnimation(POINT_75R);
	else if (valor == 9)sprite->changeAnimation(POINT_75L);
	else if (valor == 10)sprite->changeAnimation(POINT_75L);
	else if (valor == 11)sprite->changeAnimation(POINT_9L);


}

void Soldier::render()
{
	sprite->render();
}

void Soldier::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Soldier::setPosition(const glm::vec2& pos)
{
	posSoldier = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSoldier.x), float(tileMapDispl.y + posSoldier.y)));
}

float Soldier::getPosX()
{
	return float(posSoldier.x);
}

float Soldier::getPosY()
{
	return float(posSoldier.y);
}

glm::vec2 Soldier::getPosition() {

	return glm::vec2(posSoldier.x, posSoldier.y);

}

glm::vec2 Soldier::getBoxCollider() {

	return glm::vec2(40.0, 40.0);

}




