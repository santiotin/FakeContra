#include "GameOver.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum GameOverAnims
{
	GAME_OVER,
};


void GameOver::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posPower, Player* p)
{
	pos = posPower;
	lose = false;
	tileMapDispl = tileMapPos;
	startY = posPower.y;
	player = p;


	spritesheet.loadFromFile("images/gover.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.00, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(GAME_OVER, 8);
	sprite->addKeyframe(GAME_OVER, glm::vec2(0.00, 0.00));
	segslose = Time::instance().getMili();
}

void GameOver::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() != GAME_OVER)sprite->changeAnimation(GAME_OVER);
	cout << "SEGLOSE: " << segslose << endl;
	cout << "LA RESTA DA: " << Time::instance().getMili() - segslose << endl;
	if (Time::instance().getMili() - segslose < 2100) {
		if (sprite->animation() != GAME_OVER)sprite->changeAnimation(GAME_OVER);
		if (Time::instance().getMili() - segslose > 2000) {
			lose = true;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void GameOver::render()
{
	sprite->render();
}
bool GameOver::goMenu()
{
	return lose;
}
void GameOver::setPosition(glm::vec2 p) {
	pos = p;
}


