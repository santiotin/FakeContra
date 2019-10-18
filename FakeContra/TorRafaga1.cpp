#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "TorRafaga1.h"
#include "Scene.h"
#include "Game.h"


//holi


enum TorRafagaAnims
{
	POINT_9, POINT_10, POINT_11
};


void TorRafaga::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/TorRafaga.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.33, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);



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
	/*if (player->getPosX())
	{
		sprite->changeAnimation(POINT_10);
	}*/


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




