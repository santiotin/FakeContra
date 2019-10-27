#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "TorBlue.h"
#include "Game.h"



enum TorBlueAnims
{
	SHOOT, DIE
};


void TorBlue::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/TorBlue.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);


	sprite->setAnimationSpeed(SHOOT, 8);
	sprite->addKeyframe(SHOOT, glm::vec2(0.00f, 0.00f));

	shooting = false;
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;


}

void TorBlue::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	sprite->update(deltaTime);
	float posTorBlueX = getPosX();
	float posTorBlueY = getPosY();
	float distX = posTorBlueX - posPlayerX;
	if (distX < 65 && distX > -65) shooting = true;
	else if (distX > 64 && posTorBlueX > 185) {
		posTorBlueX -= 2;
		cout << posTorBlueX << endl;
		setPosition(glm::vec2(posTorBlueX, posTorBlueY));
		shooting = false;
	}
	else if (distX < -64 && posTorBlueX < 400) {
		posTorBlueX += 2;
		cout << posTorBlueX << endl;
		setPosition(glm::vec2(posTorBlueX, posTorBlueY));
		shooting = false;
	}
	if (shooting) {
		//doShoot(13.0, -65.0, distX * -0.006, 1.0, 2);
	}

}

void TorBlue::render()
{
	sprite->render();
}

void TorBlue::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void TorBlue::setPosition(const glm::vec2& pos)
{
	posTurret = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTurret.x), float(tileMapDispl.y + posTurret.y)));
}

float TorBlue::getPosX()
{
	return float(posTurret.x);
}

float TorBlue::getPosY()
{
	return float(posTurret.y);
}

glm::vec2 TorBlue::getPosition() {

	return glm::vec2(posTurret.x, posTurret.y);

}

glm::vec2 TorBlue::getBoxCollider() {

	return glm::vec2(32.0, 32.0);

}

glm::vec2 TorBlue::getStartP() {
	return glm::vec2(0.0, 0.0);
}




