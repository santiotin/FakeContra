#include "Bullet.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum BulletAnims
{
	BULLET_LIVE,
};


void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, float dx, float dy)
{
	desplX = dx;
	desplY = dy;
	die = false;
	tileMapDispl = tileMapPos;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(BULLET_LIVE, 8);
	sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.60f, 0.00f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posX), float(tileMapDispl.y + posY)));

}

void Bullet::setPosition(float x, float y)
{
	posX = x;
	posY = y;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posX), float(tileMapDispl.y + posY)));
}

void Bullet::update(int deltaTime)
{
	sprite->update(deltaTime);

	posX += desplX;
	posY += desplY;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posX), float(tileMapDispl.y + posY)));
}

void Bullet::render()
{
	sprite->render();
}