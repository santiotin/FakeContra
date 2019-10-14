#include "Torreta1.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum TurretAnims
{
	POINT_1, POINT_2, POINT_3, POINT_4, POINT_5, POINT_6, POINT_7, POINT_8, POINT_9, POINT_10, POINT11, POINT_12
};


void Turret1::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	
	spritesheet.loadFromFile("images/Torreta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(POINT_1, 8);
	sprite->addKeyframe(POINT_1, glm::vec2(0.55f, 0.00f));

	sprite->setAnimationSpeed(POINT_2, 8);
	sprite->addKeyframe(POINT_2, glm::vec2(0.0f, 0.00f));

	sprite->setAnimationSpeed(POINT_3, 8);
	sprite->addKeyframe(POINT_3, glm::vec2(0.55f, 0.05f));

	sprite->setAnimationSpeed(POINT_4, 8);
	sprite->addKeyframe(POINT_4, glm::vec2(0.55f, 0.00f));

	sprite->setAnimationSpeed(POINT_5, 8);
	sprite->addKeyframe(POINT_5, glm::vec2(0.0f, 0.00f));

	sprite->setAnimationSpeed(POINT_6, 8);
	sprite->addKeyframe(POINT_6, glm::vec2(0.55f, 0.05f));

	sprite->setAnimationSpeed(POINT_7, 8);
	sprite->addKeyframe(POINT_7, glm::vec2(0.55f, 0.00f));

	sprite->setAnimationSpeed(POINT_8, 8);
	sprite->addKeyframe(POINT_8, glm::vec2(0.0f, 0.00f));

	sprite->setAnimationSpeed(POINT_9, 8);
	sprite->addKeyframe(POINT_9, glm::vec2(0.55f, 0.05f));

	sprite->setAnimationSpeed(POINT_10, 8);
	sprite->addKeyframe(POINT_10, glm::vec2(0.55f, 0.00f));

	sprite->setAnimationSpeed(POINT_11, 8);
	sprite->addKeyframe(POINT_11, glm::vec2(0.0f, 0.00f));

	sprite->setAnimationSpeed(POINT_12, 8);
	sprite->addKeyframe(POINT_12, glm::vec2(0.55f, 0.05f));

	


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));

}

void Turret1::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
	}
}

void Turret1::render()
{
	sprite->render();
}

void Turret1::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}


float Turret1::getPosX()
{
	return float(posPlayer.x);
}




