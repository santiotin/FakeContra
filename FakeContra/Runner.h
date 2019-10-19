#ifndef _RUNNER_INCLUDE
#define _RUNNER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class Runner
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	float getPosX(), getPosY();

private:
	glm::ivec2 tileMapDispl, posRunner;
	int startY;
	float distX, distY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 

