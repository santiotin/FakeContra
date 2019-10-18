#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "BulletManager.h"
#include "Turret1.h"
#include "TorRafaga1.h"
#include "EnemyManager.h"
#include "Menu.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void updateCamera();

private:
	void initShaders();

private:
	TileMap *map;

	Player *player;
	
	EnemyManager *enemyManager;

	Menu *menu;

	BulletManager *bManager;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	bool inMenu;


};


#endif // _SCENE_INCLUDE

