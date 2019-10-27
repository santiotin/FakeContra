#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Sprite.h"
#include "TileMap.h"


#pragma once
class Menu
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	bool canStartGame();

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;

	long long lastPulse;
};



#endif // _MENU_INCLUDE
