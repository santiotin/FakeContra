#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Turret1.h"
#include "Game.h"





enum Turret1Anims
{
	POINT_1, POINT_2, POINT_3, POINT_4, POINT_5, POINT_6, POINT_7, POINT_8, POINT_9, POINT_10, POINT_11, POINT_12
};


void Turret::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Torreta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25, 0.33), &spritesheet, &shaderProgram); 
	sprite->setNumberAnimations(12);


	sprite->setAnimationSpeed(POINT_1, 8);
	sprite->addKeyframe(POINT_1, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(POINT_2, 8);
	sprite->addKeyframe(POINT_2, glm::vec2(0.00f, 0.25f));

	sprite->setAnimationSpeed(POINT_3, 8);
	sprite->addKeyframe(POINT_3, glm::vec2(0.00f, 0.50f));

	sprite->setAnimationSpeed(POINT_4, 8);
	sprite->addKeyframe(POINT_4, glm::vec2(0.00f, 0.75f));

	sprite->setAnimationSpeed(POINT_5, 8);
	sprite->addKeyframe(POINT_5, glm::vec2(0.33f, 0.00f));

	sprite->setAnimationSpeed(POINT_6, 8);
	sprite->addKeyframe(POINT_6, glm::vec2(0.33f, 0.25f));

	sprite->setAnimationSpeed(POINT_7, 8);
	sprite->addKeyframe(POINT_7, glm::vec2(0.33f, 0.50f));

	sprite->setAnimationSpeed(POINT_8, 8);
	sprite->addKeyframe(POINT_8, glm::vec2(0.33f, 0.75f));

	sprite->setAnimationSpeed(POINT_9, 8);
	sprite->addKeyframe(POINT_9, glm::vec2(0.66f, 0.00f));

	sprite->setAnimationSpeed(POINT_10, 8);
	sprite->addKeyframe(POINT_10, glm::vec2(0.66f, 0.25f));

	sprite->setAnimationSpeed(POINT_11, 8);
	sprite->addKeyframe(POINT_11, glm::vec2(0.66f, 0.50f));

	sprite->setAnimationSpeed(POINT_12, 8);
	sprite->addKeyframe(POINT_12, glm::vec2(0.66f, 0.75f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	

}

void Turret::update(int deltaTime, int posPlayerX)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		
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
	posTurret= pos;
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




