#ifndef _TURRET1_INCLUDE
#define _TURRET1_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class Turret
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int posPlayerX);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	float getPosX(), getPosY();

private:
	glm::ivec2 tileMapDispl, posTurret;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 


