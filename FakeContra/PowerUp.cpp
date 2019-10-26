#include "PowerUp.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#define powerOffset 64

enum PowerUpAnims
{
	POWER_UP, 
};


void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posPower, Player* p)
{
	pos = posPower;
	die = false;
	tileMapDispl = tileMapPos;
	startY = posPower.y;
	player = p;

	jumpHeight = 32; //96
	jumpAngleStep = 4; //4
	jumpAngle = 0;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	
	sprite->setAnimationSpeed(POWER_UP, 8);
	sprite->addKeyframe(POWER_UP, glm::vec2(0.60f, 0.25f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void PowerUp::update(int deltaTime)
{
	sprite->update(deltaTime);

	jumpAngle += jumpAngleStep;
	pos.y = int(startY - jumpHeight * sin(3.14159f * jumpAngle / 180.f));

	if (isPlayerInsideHitBox()) {
		setDead();
		player->setHasPower();
	}
	

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void PowerUp::render()
{
	if(!die) sprite->render();
}


bool PowerUp::isDead() {
	return die;
}

void PowerUp::setDead() {
	die = true;
}

bool PowerUp::isPlayerInsideHitBox() {
	if (pos.x > player->getPosX() && pos.x < (player->getPosX() + player->getBox().x)) {
		if ((pos.y + powerOffset) > player->getPosY() + player->getStartP().y && (pos.y + powerOffset) < (player->getPosY() + player->getStartP().y + player->getBox().y)) {
			if (!die) return true;
			else return false;
		}
		else return false;
	}
	else return false;

}
