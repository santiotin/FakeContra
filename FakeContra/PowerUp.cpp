#include "PowerUp.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum PowerUpAnims
{
	POWER_UP, 
};


void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet)
{
	pos = posBullet;
	die = false;
	tileMapDispl = tileMapPos;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);


	
	sprite->setAnimationSpeed(POWER_UP, 8);
	sprite->addKeyframe(POWER_UP, glm::vec2(0.60f, 0.00f));

	

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void PowerUp::update(int deltaTime)
{
	sprite->update(deltaTime);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void PowerUp::render()
{
	sprite->render();
}


bool PowerUp::isDead() {
	return die;
}

void PowerUp::setDead() {
	die = true;


}
