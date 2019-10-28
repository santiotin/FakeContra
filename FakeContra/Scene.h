#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PlayerLevel2.h"
#include "PlayerLevel3.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "Menu.h"
#include "MapLevel2.h"
#include "MapLevel3.h"
#include "LifeIcon.h"
#include "PowerUpIcon.h"
#include "PowerUp.h"
#include "SpreadGun.h"


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
	int getMode();
	void setMode(int m);
	int getEnum(int s);

	

private:
	void initShaders();

private:
	TileMap *map;

	Player *player;
	PlayerLevel2* playerLevel2;
	PlayerLevel3* playerLevel3;
	LifeIcon* lifeIcon;
	PowerUpIcon* powerUpIcon;
	PowerUp* powerUp;
	SpreadGun* spreadGun;

	MapLevel2 *lvl2;
	MapLevel3* lvl3;

	Menu *menu;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int mode;
	bool godMode;

	long long godModeTime;

};


#endif // _SCENE_INCLUDE

