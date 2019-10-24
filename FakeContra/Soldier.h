#ifndef _SOLDIER_INCLUDE
#define _SOLDIER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"




class Soldier : public Enemy
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; 
	void update(int deltaTime, float posPlayerX, float posPlayerY) override;
	void render() override;

	void setTileMap(TileMap* tileMap) override;
	void setPosition(const glm::vec2& pos) override;

	glm::vec2 getPosition() override;
	glm::vec2 getBoxCollider() override;

	float getPosX(), getPosY();

	void doShoot(float posX, float posY, float dirX, float dirY, float speed);
	void shootFromAnimation();

private:
	glm::ivec2 tileMapDispl, posSoldier;
	int startY;
	float distX, distY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	long long lastShoot;

};


#endif