#ifndef _BULLET_INCLUDE
#define _BULLET_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


#pragma once
class Bullet
{
	
public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, float dx, float dy);
	void update(int deltaTime);
	void render();

	void setPosition(float x, float y);


private:
	glm::ivec2 tileMapDispl;
	float desplX, desplY;
	float posX, posY;
	bool die;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};

#endif // _BULLET_INCLUDE

