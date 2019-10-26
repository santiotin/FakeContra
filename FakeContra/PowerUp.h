#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


#pragma once
class PowerUp
{

public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet);
	void update(int deltaTime);
	void render();

	bool isDead();
	void setDead();



private:
	glm::ivec2 tileMapDispl;
	glm::vec2 pos;
	bool die;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};

#endif // _POWERUP_INCLUDE