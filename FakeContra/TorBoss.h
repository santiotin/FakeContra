#ifndef _TORBOS_INCLUDE
#define _TORBOS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"



class TorBoss : public Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	float getPosX(), getPosY();

	glm::vec2 getStartP();

	glm::vec2 getPosition() override;
	glm::vec2 getBoxCollider() override;

private:
	glm::ivec2 tileMapDispl, posTurret;
	int startY;
	float distX, distY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif 



