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


void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet, glm::vec2 dirBullet, float s, int type)
{
	pos = posBullet;
	dir = dirBullet;
	die = false;
	speed = s;
	tileMapDispl = tileMapPos;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	
	if (type == 0) {
		sprite->setAnimationSpeed(BULLET_LIVE, 8);
		sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.60f, 0.00f));
	}
	else { 
		sprite->setAnimationSpeed(BULLET_LIVE, 8);
		sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.65f, 0.05f)); 
		//sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.70f, 0.05f));
		//sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.60f, 0.10f));
	}

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}


void Bullet::update(int deltaTime)
{
	sprite->update(deltaTime);

	pos.x += dir.x * speed;
	pos.y += dir.y * speed;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Bullet::render()
{
	sprite->render();
}

glm::vec2 Bullet::getDirection() {
	return dir;
}

glm::vec2 Bullet::getPosition() {
	return pos;
}