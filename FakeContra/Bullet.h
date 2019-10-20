#ifndef _BULLET_INCLUDE
#define _BULLET_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


#pragma once
class Bullet
{
	
public:


	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 posBullet, glm::vec2 dirBullet, float s, int type);
	void update(int deltaTime);
	void render();

	//void setPosition(glm::vec2 posBullet);
	//void setDirection(glm::vec2 dirBullet);

	glm::vec2 getPosition();
	glm::vec2 getDirection();


private:
	glm::ivec2 tileMapDispl;
	glm::vec2 dir;
	glm::vec2 pos;
	float speed;
	bool die;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};

#endif // _BULLET_INCLUDE

