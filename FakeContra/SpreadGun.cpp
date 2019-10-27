#include "SpreadGun.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#define spreadOffset 64

enum SpreadGunAnims
{
	SPREADGUN,
};

void SpreadGun::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posPower, Player* p)
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

	sprite->setAnimationSpeed(SPREADGUN, 8);
	sprite->addKeyframe(SPREADGUN, glm::vec2(0.60f, 0.40f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void SpreadGun::update(int deltaTime)
{
	sprite->update(deltaTime);

	jumpAngle += jumpAngleStep;
	pos.y = int(startY - jumpHeight * sin(3.14159f * jumpAngle / 180.f));

	if (isPlayerInsideHitBox()) {
		setDead();
		player->setHasSpreadGun();
	}


	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void SpreadGun::render()
{
	if (!die) sprite->render();
}

bool SpreadGun::isDead() {
	return die;
}

void SpreadGun::setDead() {
	die = true;
}

bool SpreadGun::isPlayerInsideHitBox() {
	if (pos.x > player->getPosX() && pos.x < (player->getPosX() + player->getBox().x)) {
		if ((pos.y + spreadOffset) > player->getPosY() + player->getStartP().y && (pos.y + spreadOffset) < (player->getPosY() + player->getStartP().y + player->getBox().y)) {
			if (!die) return true;
			else return false;
		}
		else return false;
	}
	else return false;

}
