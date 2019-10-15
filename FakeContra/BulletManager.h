#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE
#include <glm/glm.hpp>
#include <vector> 
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Bullet.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


#pragma once
class BulletManager
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);

	void createBullet(float px, float py, float dx, float dy);

private:


private:
	TileMap* map;
	glm::ivec2 tileMapDispl;
	ShaderProgram sh;
	vector<Bullet*> bullets;

};



#endif // _BULLETMANAGER_INCLUDE

