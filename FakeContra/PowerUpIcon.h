#ifndef _POWERUPICON_INCLUDE
#define _POWERUPICON_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


#pragma once
class PowerUpIcon
{

public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();


	void setPosition(glm::vec2 posLife);
	void changePower(bool lp);
	//void setDirection(glm::vec2 dirBullet);


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 pos;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;


};

#endif // _POWERUPICON_INCLUDE
