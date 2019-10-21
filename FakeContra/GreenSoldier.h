#ifndef _GREENSOLDIER_INCLUDE
#define _GREENSOLDIER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class GreenSoldier
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	float getPosX(), getPosY();

private:
	glm::ivec2 tileMapDispl, posGreenSoldier;
	int startY;
	bool shooting;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 


