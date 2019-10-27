#ifndef _SPREADGUN_INCLUDE
#define _SPREADGUN_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


#pragma once
class SpreadGun
{

public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet, Player* p);
	void update(int deltaTime);
	void render();

	bool isDead();
	void setDead();

	bool isPlayerInsideHitBox();



private:
	glm::ivec2 tileMapDispl;
	glm::vec2 pos;
	bool die;
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