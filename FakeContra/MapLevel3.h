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
	bool goMenu();
	int count1, count2, count3, count4, count5, count6;

private:
	long long segs, segswin;
	bool fase1, fase2, fase3, fase4, faseBoss, faseEnd, done, win, end;
	glm::ivec2 tileMapDispl, posMapLevel2;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 


