#include "Bullet.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum BulletAnims
{
	BULLET_LIVE, BULLET_DEAD
};


void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet, glm::vec2 dirBullet, float s, int t)
{
	pos = posBullet;
	dir = dirBullet;
	die = false;
	speed = s;
	tileMapDispl = tileMapPos;
	deadTime = 0.0;
	type = t;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	
	if (type == 0) {
		sprite->setAnimationSpeed(BULLET_LIVE, 8);
		sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.60f, 0.00f));

		sprite->setAnimationSpeed(BULLET_DEAD, 8);
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.60f, 0.15f));
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.65f, 0.15f));
	}
	else if(type == 1){ 
		sprite->setAnimationSpeed(BULLET_LIVE, 8);
		sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.65f, 0.05f)); 
		sprite->setAnimationSpeed(BULLET_DEAD, 8);
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.60f, 0.15f));
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.65f, 0.15f));
	}
	else if(type == 2){
		sprite->setAnimationSpeed(BULLET_LIVE, 8);
		sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.60f, 0.30f));
		sprite->setAnimationSpeed(BULLET_DEAD, 8);
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.60f, 0.15f));
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.65f, 0.15f));
	}
	else {
		sprite->setAnimationSpeed(BULLET_LIVE, 8);
		sprite->addKeyframe(BULLET_LIVE, glm::vec2(0.65f, 0.25f));
		sprite->setAnimationSpeed(BULLET_DEAD, 8);
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.60f, 0.15f));
		sprite->addKeyframe(BULLET_DEAD, glm::vec2(0.65f, 0.15f));
	}

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void Bullet::update(int deltaTime)
{
	sprite->update(deltaTime);
	pos.x += dir.x * speed;
	pos.y += dir.y * speed;

	deadTime = deadTime + 0.1;

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

glm::vec2 Bullet::getInversePosition() {
	if (type == 0 || type == 1) {
		return glm::vec2(pos.x + 10.0, pos.y);
	} 
	else if (type == 2) {
		return glm::vec2(pos.x + 50.0, pos.y);
	}
	else if (type == 3) {
		return glm::vec2(pos.x + 50.0, pos.y);
	}
}

bool Bullet::isDead() {
	if (sprite->animation() == BULLET_DEAD && deadTime > 0.4) return true;
	else return false;
}

void Bullet::setDead() {
	if (sprite->animation() != BULLET_DEAD) {
		sprite->changeAnimation(BULLET_DEAD);
		deadTime = 0.0;
	}
	
	
}


