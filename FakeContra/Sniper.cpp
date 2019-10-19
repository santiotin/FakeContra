#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sniper.h"
#include "Scene.h"
#include "Game.h"




enum SniperAnims
{
	HEAT_L, HEAT_R, POINT_L, POINT_R, SHOOT_L, SHOOT_R
};


void Sniper::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Sniper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.33, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);



	sprite->setAnimationSpeed(HEAT_L, 8);
	sprite->addKeyframe(HEAT_L, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(POINT_L, 8);
	sprite->addKeyframe(POINT_L, glm::vec2(0.33f, 0.00f));

	sprite->setAnimationSpeed(SHOOT_L, 8);
	sprite->addKeyframe(SHOOT_L, glm::vec2(0.66f, 0.00f));

	sprite->setAnimationSpeed(HEAT_R, 8);
	sprite->addKeyframe(HEAT_R, glm::vec2(0.00f, 0.50f));

	sprite->setAnimationSpeed(POINT_R, 8);
	sprite->addKeyframe(POINT_R, glm::vec2(0.33f, 0.50f));

	sprite->setAnimationSpeed(SHOOT_R, 8);
	sprite->addKeyframe(SHOOT_R, glm::vec2(0.66f, 0.50f));



	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void Sniper::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posSniperX = getPosX();
	float posSniperY = getPosY();

	distX = posSniperX - posPlayerX;

	distY = posSniperY - posPlayerY;


	if (distX < 20) sprite->changeAnimation(HEAT_L);


}

void Sniper::render()
{
	sprite->render();
}

void Sniper::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Sniper::setPosition(const glm::vec2& pos)
{
	posSniper = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSniper.x), float(tileMapDispl.y + posSniper.y)));
}

float Sniper::getPosX()
{
	return float(posSniper.x);
}

float Sniper::getPosY()
{
	return float(posSniper.y);
}




