#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "BulletManager.h"
#include "Turret1.h"
#include "TorRafaga1.h"
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

	Menu *menu;

	BulletManager *bManager;

	Turret *turret1;
	Turret* turret2;
	Turret* turret3;
	Turret* turret4;
	Turret* turret5;
	Turret* turret6;

	TorRafaga *torrafaga1;
	TorRafaga* torrafaga2;
	TorRafaga* torrafaga3;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	bool inMenu;


};


#endif // _SCENE_INCLUDE

