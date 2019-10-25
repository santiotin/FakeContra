#ifndef _LIFEICON_INCLUDE
#define _LIFEICON_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


#pragma once
class LifeIcon
{

public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();


	void setPosition(glm::vec2 posLife);
	void changeLife(int l);
	//void setDirection(glm::vec2 dirBullet);


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 pos;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;


};

#endif // _LIFEICON_INCLUDE
