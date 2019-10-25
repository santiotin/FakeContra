#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <vector>
#include "Sprite.h"
#include "TileMap.h"

class Enemy {
public:

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime, float posPlayerX, float posPlayerY);
	virtual void render();

	virtual void setTileMap(TileMap* tileMap);
	virtual void setPosition(const glm::vec2& pos);

	virtual glm::vec2 getPosition();
	virtual glm::vec2 getBoxCollider();

	virtual glm::vec2 getStartP();
							   
private:
	int life;
};

#endif // _PLAYER_INCLUDE