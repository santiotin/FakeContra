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
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setBox(glm::vec2 box);
	void setDeadState(bool dead);
	bool Player::getDeadState();

	float getPosX();
	float getPosY();
	glm::vec2 getPosition();
	glm::vec2 getBox();
	glm::vec2 getStartP();
	void setStartP(glm::vec2 start);

	void doShoot(float posX, float posY, float dirX, float dirY, float speed);

	
	int Player::getDeadTime();
	int Player::getLifes();
	
private:
	bool bJumping, bDir, bSwim, isDead, superMode;
	glm::ivec2 tileMapDispl, posPlayer, boxPlayer, startP;
	int jumpAngle, startY;
	long long lastShoot;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	int lifes;
	int deadTime;

	float speedLinearBullet;
	float speedDiagBullet;
	float walkStep;
	float fallStep;
	float jumpHeight;
	float jumpAngleStep;
	
};


#endif // _PLAYER_INCLUDE


