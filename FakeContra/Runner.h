#ifndef _RUNNER_INCLUDE
#define _RUNNER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"




class Runner : public Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime, float posPlayerX, float posPlayerY) override;
	void render() override;

	void setTileMap(TileMap* tileMap) override;
	void setPosition(const glm::vec2& pos) override;

	float getPosX(), getPosY();

	glm::vec2 getPosition() override;
	glm::vec2 getBoxCollider() override;

private:
	glm::ivec2 tileMapDispl, posRunner;
	int startY;
	float distX, distY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif