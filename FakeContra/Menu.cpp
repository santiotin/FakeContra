#include "Menu.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum MenuAnims
{
	MENU_PLAY, MENU_CONTROLS, MENU_CREDITS, VIEW_CREDITS, VIEW_CONTROLS
};

void Menu::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	lastPulse = 0;
	spritesheet.loadFromFile("images/menuCompleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 540), glm::vec2(0.3333, 0.3333), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	//STAND FORW RIGHT LEFT SHOOT NO SHOT
	sprite->setAnimationSpeed(MENU_PLAY, 8);
	sprite->addKeyframe(MENU_PLAY, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(MENU_CONTROLS, 8);
	sprite->addKeyframe(MENU_CONTROLS, glm::vec2(0.3333f, 0.00f));

	sprite->setAnimationSpeed(MENU_CREDITS, 8);
	sprite->addKeyframe(MENU_CREDITS, glm::vec2(0.66666f, 0.00f));

	sprite->setAnimationSpeed(VIEW_CREDITS, 8);
	sprite->addKeyframe(VIEW_CREDITS, glm::vec2(0.0000f, 0.3333f));

	sprite->setAnimationSpeed(VIEW_CONTROLS, 8);
	sprite->addKeyframe(VIEW_CONTROLS, glm::vec2(0.3333f, 0.3333f));
	


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

}

void Menu::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (sprite->animation() == MENU_PLAY) {
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(MENU_CONTROLS);
			lastPulse = Time::instance().getMili();
		}
	}
	else if (sprite->animation() == MENU_CONTROLS) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(MENU_PLAY);
			lastPulse = Time::instance().getMili();
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(MENU_CREDITS);
			lastPulse = Time::instance().getMili();
		}
		else if (Game::instance().getKey(13) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(VIEW_CONTROLS);
			lastPulse = Time::instance().getMili();
		}
	}
	else if (sprite->animation() == MENU_CREDITS) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(MENU_CONTROLS);
			lastPulse = Time::instance().getMili();
		}
		else if (Game::instance().getKey(13) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(VIEW_CREDITS);
			lastPulse = Time::instance().getMili();
		}
	}
	else if (sprite->animation() == VIEW_CONTROLS) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(MENU_CONTROLS);
			lastPulse = Time::instance().getMili();
		}
	}
	else if (sprite->animation() == VIEW_CREDITS) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Time::instance().isAbleToShoot(lastPulse)) {
			sprite->changeAnimation(MENU_CREDITS);
			lastPulse = Time::instance().getMili();
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void Menu::render()
{
	sprite->render();
}

bool Menu::canStartGame() {
	if (sprite->animation() == MENU_PLAY) return true;
	else return false;
}


