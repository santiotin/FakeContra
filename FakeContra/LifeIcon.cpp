#include "LifeIcon.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum LifeAnims
{
	Life_1, Life_2, Life_3, Life_0
};


void LifeIcon::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	tileMapDispl = tileMapPos;

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(Life_1, 8);
	sprite->addKeyframe(Life_1, glm::vec2(0.60f, 0.20f));

	sprite->setAnimationSpeed(Life_2, 8);
	sprite->addKeyframe(Life_2, glm::vec2(0.65f, 0.20f));

	sprite->setAnimationSpeed(Life_3, 8);
	sprite->addKeyframe(Life_3, glm::vec2(0.70f, 0.20f));

	sprite->setAnimationSpeed(Life_0, 8);
	sprite->addKeyframe(Life_0, glm::vec2(0.75f, 0.20f));
	
	sprite->changeAnimation(Life_3);
	pos = glm::vec2(30.0, 0.0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void LifeIcon::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void LifeIcon::render()
{
	sprite->render();
}

void LifeIcon::setPosition(glm::vec2 posLife) {
	pos = posLife;
}

void LifeIcon::changeLife(int l) {
	if (l == 1) {
		sprite->changeAnimation(Life_1);
	}
	else if (l == 2) {
		sprite->changeAnimation(Life_2);
	}
	else if (l == 3){
		sprite->changeAnimation(Life_3);
	}
	else if (l == 0) {
		sprite->changeAnimation(Life_0);
	}
}