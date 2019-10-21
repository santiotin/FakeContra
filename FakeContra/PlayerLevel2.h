#ifndef _PLAYER_LEVEL_2_INCLUDE
#define _PLAYER_LEVEL_2_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Time.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class PlayerLevel2
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setBox(glm::vec2 box);
	void setDeadState(bool dead);

	float getPosX();
	float getPosY();
	glm::vec2 getPosition();
	glm::vec2 getBox();
	void doShoot(float posX, float posY, float dirX, float dirY);

private:
	bool bJumping, bDir, isDead;
	glm::ivec2 tileMapDispl, posPlayer, boxPlayer;
	int jumpAngle, startY;
	long long lastShoot;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _PLAYER_LEVEL_2_INCLUDE


