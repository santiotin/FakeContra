#ifndef _MAPLEVEL2_INCLUDE
#define _MAPLEVEL2_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class MapLevel2
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	//void update(int deltaTime, ShaderProgram& shaderProgram);
	void render();

	void setPosition(const glm::vec2& pos);

	int count;

private:
	bool fase1, fase2, fase3, fase4;
	glm::ivec2 tileMapDispl, posMapLevel2;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 


