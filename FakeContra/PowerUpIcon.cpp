#include "PowerUpIcon.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum PowerAnims
{
	Has_Power, No_Power
};


void PowerUpIcon::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	tileMapDispl = tileMapPos;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(Has_Power, 8);
	sprite->addKeyframe(Has_Power, glm::vec2(0.60f, 0.25f));

	sprite->setAnimationSpeed(No_Power, 8);
	sprite->addKeyframe(No_Power, glm::vec2(0.65f, 0.25f));


	sprite->changeAnimation(No_Power);
	pos = glm::vec2(0.0, 0.0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void PowerUpIcon::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void PowerUpIcon::render()
{
	sprite->render();
}

void PowerUpIcon::setPosition(glm::vec2 posLife) {
	pos = posLife;
}

void PowerUpIcon::changePower(bool p) {
	if (p) sprite->changeAnimation(Has_Power);
	else sprite->changeAnimation(No_Power);
}