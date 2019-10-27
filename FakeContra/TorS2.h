#ifndef _TORS2_INCLUDE
#define _TORS2_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"



class TorS2 : public Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime, float posPlayerX, float posPlayerY, bool isDead) override;
	void render() override;

	void setTileMap(TileMap* tileMap) override;
	void setPosition(const glm::vec2& pos) override;

	float getPosX(), getPosY();

	glm::vec2 getStartP() override;

	glm::vec2 getPosition() override;
	glm::vec2 getBoxCollider() override;

	void doShoot(float desplX, float desplY, float dirX, float dirY, float speed);

private:
	glm::ivec2 tileMapDispl, posTurret;
	int startY;
	float distX, distY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	long long lastShoot;

};


#endif 


