#include "Menu.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum MenuAnims
{
	MENU_PLAYER_1, MENU_PLAYER_2 
};

void Menu::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 540), glm::vec2(0.5, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	//STAND FORW RIGHT LEFT SHOOT NO SHOT
	sprite->setAnimationSpeed(MENU_PLAYER_1, 8);
	sprite->addKeyframe(MENU_PLAYER_1, glm::vec2(0.00f, 0.00f));
	sprite->setAnimationSpeed(MENU_PLAYER_2, 8);
	sprite->addKeyframe(MENU_PLAYER_2, glm::vec2(0.50f, 0.00f));
	


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

}

void Menu::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (sprite->animation() == MENU_PLAYER_1 && Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		sprite->changeAnimation(MENU_PLAYER_2);
	}
	else if (sprite->animation() == MENU_PLAYER_2 && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		sprite->changeAnimation(MENU_PLAYER_1);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void Menu::render()
{
	sprite->render();
}


