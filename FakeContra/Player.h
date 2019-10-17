#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Time.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, BulletManager *bManager);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

	float getPosX();
	void doShoot(float posX, float posY, float dirX, float dirY, float speed);
	
private:
	bool bJumping, bDir, bSwim;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	long long lastShoot;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	BulletManager *bManager;

};


#endif // _PLAYER_INCLUDE


