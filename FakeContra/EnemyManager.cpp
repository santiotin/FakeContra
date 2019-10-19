#include "EnemyManager.h"
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_TURRET1_X_TILES 102
#define INIT_TURRET1_Y_TILES 8.4
#define INIT_TURRET2_X_TILES 114
#define INIT_TURRET2_Y_TILES 8.4
#define INIT_TURRET3_X_TILES 78
#define INIT_TURRET3_Y_TILES 10.4
#define INIT_TURRET4_X_TILES 186
#define INIT_TURRET4_Y_TILES 12.4
#define INIT_TURRET5_X_TILES 194
#define INIT_TURRET5_Y_TILES 12.4
#define INIT_TURRET6_X_TILES 214
#define INIT_TURRET6_Y_TILES 12.4

#define INIT_TORRAFAGA1_X_TILES 136
#define INIT_TORRAFAGA1_Y_TILES 4.4
#define INIT_TORRAFAGA2_X_TILES 172
#define INIT_TORRAFAGA2_Y_TILES 8.4
#define INIT_TORRAFAGA3_X_TILES 128
#define INIT_TORRAFAGA3_Y_TILES 10.4

#define INIT_RUNNER1_X_TILES 15
#define INIT_RUNNER1_Y_TILES 2

#define INIT_SOLDIER1_X_TILES 18
#define INIT_SOLDIER1_Y_TILES 2

#define INIT_SNIPER1_X_TILES 21
#define INIT_SNIPER1_Y_TILES 2

void EnemyManager::init(TileMap *tileMap, ShaderProgram& shaderProgram)//pasa tmb lvl
{
	Turret *turret1 = new Turret();
	turret1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	turret1->setPosition(glm::vec2((INIT_TURRET1_X_TILES * tileMap->getTileSize()), INIT_TURRET1_Y_TILES * tileMap->getTileSize()));
	turret1->setTileMap(tileMap);
	vecTurret.push_back(turret1);

	Turret *turret2 = new Turret();
	turret2->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	turret2->setPosition(glm::vec2((INIT_TURRET2_X_TILES * tileMap->getTileSize()), INIT_TURRET2_Y_TILES * tileMap->getTileSize()));
	turret2->setTileMap(tileMap);
	vecTurret.push_back(turret2);

	Turret *turret3 = new Turret();
	turret3->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	turret3->setPosition(glm::vec2((INIT_TURRET3_X_TILES * tileMap->getTileSize()), INIT_TURRET3_Y_TILES * tileMap->getTileSize()));
	turret3->setTileMap(tileMap);
	vecTurret.push_back(turret3);

	Turret *turret4 = new Turret();
	turret4->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	turret4->setPosition(glm::vec2((INIT_TURRET4_X_TILES * tileMap->getTileSize()), INIT_TURRET4_Y_TILES * tileMap->getTileSize()));
	turret4->setTileMap(tileMap);
	vecTurret.push_back(turret4);

	Turret *turret5 = new Turret();
	turret5->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	turret5->setPosition(glm::vec2((INIT_TURRET5_X_TILES * tileMap->getTileSize()), INIT_TURRET5_Y_TILES * tileMap->getTileSize()));
	turret5->setTileMap(tileMap);
	vecTurret.push_back(turret5);

	Turret *turret6 = new Turret();
	turret6->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	turret6->setPosition(glm::vec2((INIT_TURRET6_X_TILES * tileMap->getTileSize()), INIT_TURRET6_Y_TILES * tileMap->getTileSize()));
	turret6->setTileMap(tileMap);
	vecTurret.push_back(turret6);

	TorRafaga *torrafaga1 = new TorRafaga();
	torrafaga1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	torrafaga1->setPosition(glm::vec2((INIT_TORRAFAGA1_X_TILES * tileMap->getTileSize()), INIT_TORRAFAGA1_Y_TILES * tileMap->getTileSize()));
	torrafaga1->setTileMap(tileMap);
	vecTorRafaga.push_back(torrafaga1);
	TorRafaga *torrafaga2 = new TorRafaga();
	torrafaga2->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	torrafaga2->setPosition(glm::vec2((INIT_TORRAFAGA2_X_TILES * tileMap->getTileSize()), INIT_TORRAFAGA2_Y_TILES * tileMap->getTileSize()));
	torrafaga2->setTileMap(tileMap);
	vecTorRafaga.push_back(torrafaga2);
	TorRafaga *torrafaga3 = new TorRafaga();
	torrafaga3->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	torrafaga3->setPosition(glm::vec2((INIT_TORRAFAGA3_X_TILES * tileMap->getTileSize()), INIT_TORRAFAGA3_Y_TILES * tileMap->getTileSize()));
	torrafaga3->setTileMap(tileMap);
	vecTorRafaga.push_back(torrafaga3);

	Runner* runner1 = new Runner();
	runner1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	runner1->setPosition(glm::vec2((INIT_RUNNER1_X_TILES * tileMap->getTileSize()), INIT_RUNNER1_Y_TILES * tileMap->getTileSize()));
	runner1->setTileMap(tileMap);
	vecRunner.push_back(runner1);

	Soldier* soldier1 = new Soldier();
	soldier1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier1->setPosition(glm::vec2((INIT_RUNNER1_X_TILES * tileMap->getTileSize()), INIT_RUNNER1_Y_TILES * tileMap->getTileSize()));
	soldier1->setTileMap(tileMap);
	vecSoldier.push_back(soldier1);

	Sniper* sniper1 = new Sniper();
	sniper1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	sniper1->setPosition(glm::vec2((INIT_RUNNER1_X_TILES * tileMap->getTileSize()), INIT_RUNNER1_Y_TILES * tileMap->getTileSize()));
	sniper1->setTileMap(tileMap);
	vecSniper.push_back(sniper1);
}

void EnemyManager::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	for (Turret* t : vecTurret) t->update(deltaTime, posPlayerX, posPlayerY);
	for (TorRafaga* tr : vecTorRafaga) tr->update(deltaTime, posPlayerX, posPlayerY);
	for (Runner* r : vecRunner) r->update(deltaTime, posPlayerX, posPlayerY);
	for (Soldier* so : vecSoldier) so->update(deltaTime, posPlayerX, posPlayerY);
	for (Sniper* sn : vecSniper) sn->update(deltaTime, posPlayerX, posPlayerY);
}

void EnemyManager::render()
{
	for (Turret* t : vecTurret) t->render();
	for (TorRafaga* tr : vecTorRafaga) tr->render();
	for (Runner* r : vecRunner) r->render();
	for (Soldier* so : vecSoldier) so->render();
	for (Sniper* sn : vecSniper) sn->render();
}