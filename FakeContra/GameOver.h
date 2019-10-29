#ifndef _GAMEOVER_INCLUDE
#define _GAMEOVER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


#pragma once
class GameOver
{

public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet, Player* p);
	void update(int deltaTime);
	void render();
	bool goMenu();

	void setPosition(glm::vec2 p);


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 pos;
	bool lose;
	long long segslose;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	int jumpAngle;
	float jumpHeight;
	float jumpAngleStep;
	float startY;
	Player* player;

};

#endif // _POWERUP_INCLUDE
