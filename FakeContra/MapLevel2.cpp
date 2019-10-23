#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapLevel2.h"
#include "Game.h"





enum MapLevel2Anims
{
	FASE_1, FASE_2, FASE_3, FASE_4
};

void MapLevel2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/lvl2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(0.25, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);


	sprite->setAnimationSpeed(FASE_1, 8);
	sprite->addKeyframe(FASE_1, glm::vec2(0.00f, 0.00f));
	sprite->setAnimationSpeed(FASE_2, 8);
	sprite->addKeyframe(FASE_2, glm::vec2(0.25f, 0.00f));
	sprite->setAnimationSpeed(FASE_3, 8);
	sprite->addKeyframe(FASE_3, glm::vec2(0.50f, 0.00f));
	sprite->setAnimationSpeed(FASE_4, 8);
	sprite->addKeyframe(FASE_4, glm::vec2(0.75f, 0.00f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void MapLevel2::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTorRafX = getPosX();
	float posTorRafY = getPosY();

	sprite->changeAnimation(FASE_1);
	


}

void MapLevel2::render()
{
	sprite->render();
}



void MapLevel2::setPosition(const glm::vec2& pos)
{
	posMapLevel2 = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapLevel2.x), float(tileMapDispl.y + posMapLevel2.y)));
}

float MapLevel2::getPosX()
{
	return float(posMapLevel2.x);
}

float MapLevel2::getPosY()
{
	return float(posMapLevel2.y);
}




