#ifndef _MAPLEVEL3_INCLUDE
#define _MAPLEVEL3_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class MapLevel3
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	//void update(int deltaTime, float posPlayerX, float posPlayerY);
	void update(int deltaTime, ShaderProgram& shaderProgram);
	void render();
	bool isFaseBoss();
	void setPosition(const glm::vec2& pos);

	int count1, count2, count3, countBoss;

private:
	long long segs;
	bool fase1, fase2, fase3, fase4, faseBoss, faseEnd;
	glm::ivec2 tileMapDispl, posMapLevel2;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 


