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
#define INIT_RUNNER1_Y_TILES 6.8
#define INIT_RUNNER2_X_TILES 17
#define INIT_RUNNER2_Y_TILES 6.8
#define INIT_RUNNER3_X_TILES 20
#define INIT_RUNNER3_Y_TILES 6.8

#define INIT_SOLDIER1_X_TILES 18.8
#define INIT_SOLDIER1_Y_TILES 11.8
#define INIT_SOLDIER2_X_TILES 38.8
#define INIT_SOLDIER2_Y_TILES 11.8
#define INIT_SOLDIER3_X_TILES 80
#define INIT_SOLDIER3_Y_TILES 5.8
#define INIT_SOLDIER4_X_TILES 147
#define INIT_SOLDIER4_Y_TILES 7.8
#define INIT_SOLDIER5_X_TILES 225
#define INIT_SOLDIER5_Y_TILES 11.8
#define INIT_SOLDIER6_X_TILES 230
#define INIT_SOLDIER6_Y_TILES 11.8

#define INIT_SNIPER1_X_TILES 83
#define INIT_SNIPER1_Y_TILES 7
#define INIT_SNIPER2_X_TILES 98
#define INIT_SNIPER2_Y_TILES 5

#define INIT_GREENSOLDIER1_X_TILES 20
#define INIT_GREENSOLDIER1_Y_TILES 2

#define INIT_TORS21_X_TILES 7.45
#define INIT_TORS21_Y_TILES 6
#define INIT_TORS22_X_TILES 11.1
#define INIT_TORS22_Y_TILES 6

#define INIT_BOLS21_X_TILES 7.45
#define INIT_BOLS21_Y_TILES 7.4
#define INIT_BOLS22_X_TILES 11.1
#define INIT_BOLS22_Y_TILES 7.4

void EnemyManager::init1(TileMap *tileMap, ShaderProgram& shaderProgram)
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
	Runner* runner2 = new Runner();
	runner2->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	runner2->setPosition(glm::vec2((INIT_RUNNER2_X_TILES * tileMap->getTileSize()), INIT_RUNNER2_Y_TILES * tileMap->getTileSize()));
	runner2->setTileMap(tileMap);
	vecRunner.push_back(runner2);
	Runner* runner3 = new Runner();
	runner3->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	runner3->setPosition(glm::vec2((INIT_RUNNER3_X_TILES * tileMap->getTileSize()), INIT_RUNNER3_Y_TILES * tileMap->getTileSize()));
	runner3->setTileMap(tileMap);
	vecRunner.push_back(runner3);

	Soldier* soldier1 = new Soldier();
	soldier1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier1->setPosition(glm::vec2((INIT_SOLDIER1_X_TILES * tileMap->getTileSize()), INIT_SOLDIER1_Y_TILES * tileMap->getTileSize()));
	soldier1->setTileMap(tileMap);
	vecSoldier.push_back(soldier1);
	Soldier* soldier2 = new Soldier();
	soldier2->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier2->setPosition(glm::vec2((INIT_SOLDIER2_X_TILES * tileMap->getTileSize()), INIT_SOLDIER2_Y_TILES * tileMap->getTileSize()));
	soldier2->setTileMap(tileMap);
	vecSoldier.push_back(soldier2);
	Soldier* soldier3 = new Soldier();
	soldier3->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier3->setPosition(glm::vec2((INIT_SOLDIER3_X_TILES * tileMap->getTileSize()), INIT_SOLDIER3_Y_TILES * tileMap->getTileSize()));
	soldier3->setTileMap(tileMap);
	vecSoldier.push_back(soldier3);
	Soldier* soldier4 = new Soldier();
	soldier4->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier4->setPosition(glm::vec2((INIT_SOLDIER4_X_TILES * tileMap->getTileSize()), INIT_SOLDIER4_Y_TILES * tileMap->getTileSize()));
	soldier4->setTileMap(tileMap);
	vecSoldier.push_back(soldier4);
	Soldier* soldier5 = new Soldier();
	soldier5->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier5->setPosition(glm::vec2((INIT_SOLDIER5_X_TILES * tileMap->getTileSize()), INIT_SOLDIER5_Y_TILES * tileMap->getTileSize()));
	soldier5->setTileMap(tileMap);
	vecSoldier.push_back(soldier5);
	Soldier* soldier6 = new Soldier();
	soldier6->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	soldier6->setPosition(glm::vec2((INIT_SOLDIER6_X_TILES * tileMap->getTileSize()), INIT_SOLDIER6_Y_TILES * tileMap->getTileSize()));
	soldier6->setTileMap(tileMap);
	vecSoldier.push_back(soldier6);

	Sniper* sniper1 = new Sniper();
	sniper1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	sniper1->setPosition(glm::vec2((INIT_SNIPER1_X_TILES * tileMap->getTileSize()), INIT_SNIPER1_Y_TILES * tileMap->getTileSize()));
	sniper1->setTileMap(tileMap);
	vecSniper.push_back(sniper1);
	Sniper* sniper2 = new Sniper();
	sniper2->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	sniper2->setPosition(glm::vec2((INIT_SNIPER2_X_TILES * tileMap->getTileSize()), INIT_SNIPER2_Y_TILES * tileMap->getTileSize()));
	sniper2->setTileMap(tileMap);
	vecSniper.push_back(sniper2);
}
void EnemyManager::init2_1(TileMap* tileMap, ShaderProgram& shaderProgram)
{
	GreenSoldier* greensoldier1 = new GreenSoldier();
	greensoldier1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	greensoldier1->setPosition(glm::vec2((INIT_GREENSOLDIER1_X_TILES * tileMap->getTileSize()), INIT_GREENSOLDIER1_Y_TILES * tileMap->getTileSize()));
	greensoldier1->setTileMap(tileMap);
	vecGS.push_back(greensoldier1);
}
void EnemyManager::init2_2(TileMap* tileMap, ShaderProgram& shaderProgram)
{
	GreenSoldier* greensoldier1 = new GreenSoldier();
	greensoldier1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	greensoldier1->setPosition(glm::vec2((INIT_GREENSOLDIER1_X_TILES * tileMap->getTileSize()), INIT_GREENSOLDIER1_Y_TILES * tileMap->getTileSize()));
	greensoldier1->setTileMap(tileMap);
	vecGS.push_back(greensoldier1);

	TorS2* tors21 = new TorS2();
	tors21->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	tors21->setPosition(glm::vec2((INIT_TORS21_X_TILES * tileMap->getTileSize()), INIT_TORS21_Y_TILES * tileMap->getTileSize()));
	tors21->setTileMap(tileMap);
	vecTS.push_back(tors21);
	TorS2* tors22 = new TorS2();
	tors22->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	tors22->setPosition(glm::vec2((INIT_TORS22_X_TILES * tileMap->getTileSize()), INIT_TORS22_Y_TILES * tileMap->getTileSize()));
	tors22->setTileMap(tileMap);
	vecTS.push_back(tors22);

}
void EnemyManager::init2_3(TileMap* tileMap, ShaderProgram& shaderProgram)
{
	GreenSoldier* greensoldier1 = new GreenSoldier();
	greensoldier1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	greensoldier1->setPosition(glm::vec2((INIT_GREENSOLDIER1_X_TILES * tileMap->getTileSize()), INIT_GREENSOLDIER1_Y_TILES * tileMap->getTileSize()));
	greensoldier1->setTileMap(tileMap);
	vecGS.push_back(greensoldier1);

	TorS2* tors21 = new TorS2();
	tors21->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	tors21->setPosition(glm::vec2((INIT_TORS21_X_TILES * tileMap->getTileSize()), INIT_TORS21_Y_TILES * tileMap->getTileSize()));
	tors21->setTileMap(tileMap);
	vecTS.push_back(tors21);

	BolS2* bol21 = new BolS2();
	bol21->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	bol21->setPosition(glm::vec2((INIT_BOLS21_X_TILES * tileMap->getTileSize()), INIT_BOLS21_Y_TILES * tileMap->getTileSize()));
	bol21->setTileMap(tileMap);
	vecBS.push_back(bol21);
	BolS2* bol22 = new BolS2();
	bol22->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	bol22->setPosition(glm::vec2((INIT_BOLS22_X_TILES * tileMap->getTileSize()), INIT_BOLS22_Y_TILES * tileMap->getTileSize()));
	bol22->setTileMap(tileMap);
	vecBS.push_back(bol22);
}
void EnemyManager::init2_4(TileMap* tileMap, ShaderProgram& shaderProgram)
{
	GreenSoldier* greensoldier1 = new GreenSoldier();
	greensoldier1->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	greensoldier1->setPosition(glm::vec2((INIT_GREENSOLDIER1_X_TILES * tileMap->getTileSize()), INIT_GREENSOLDIER1_Y_TILES * tileMap->getTileSize()));
	greensoldier1->setTileMap(tileMap);
	vecGS.push_back(greensoldier1);

	TorS2* tors21 = new TorS2();
	tors21->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	tors21->setPosition(glm::vec2((INIT_TORS21_X_TILES * tileMap->getTileSize()), INIT_TORS21_Y_TILES * tileMap->getTileSize()));
	tors21->setTileMap(tileMap);
	vecTS.push_back(tors21);
	TorS2* tors22 = new TorS2();
	tors22->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	tors22->setPosition(glm::vec2((INIT_TORS22_X_TILES * tileMap->getTileSize()), INIT_TORS22_Y_TILES * tileMap->getTileSize()));
	tors22->setTileMap(tileMap);
	vecTS.push_back(tors22);

	BolS2* bol21 = new BolS2();
	bol21->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	bol21->setPosition(glm::vec2((INIT_BOLS21_X_TILES * tileMap->getTileSize()), INIT_BOLS21_Y_TILES * tileMap->getTileSize()));
	bol21->setTileMap(tileMap);
	vecBS.push_back(bol21);
	BolS2* bol22 = new BolS2();
	bol22->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	bol22->setPosition(glm::vec2((INIT_BOLS22_X_TILES * tileMap->getTileSize()), INIT_BOLS22_Y_TILES * tileMap->getTileSize()));
	bol22->setTileMap(tileMap);
	vecBS.push_back(bol22);
}

void EnemyManager::update(int deltaTime, float posPlayerX, float posPlayerY)
{
	for (Turret* t : vecTurret) t->update(deltaTime, posPlayerX, posPlayerY);
	for (TorRafaga* tr : vecTorRafaga) tr->update(deltaTime, posPlayerX, posPlayerY);
	for (Runner* r : vecRunner) r->update(deltaTime, posPlayerX, posPlayerY);
	for (Soldier* so : vecSoldier) so->update(deltaTime, posPlayerX, posPlayerY);
	for (Sniper* sn : vecSniper) sn->update(deltaTime, posPlayerX, posPlayerY);
	for (GreenSoldier* gs : vecGS) gs->update(deltaTime, posPlayerX, posPlayerY);
	for (TorS2* ts : vecTS) ts->update(deltaTime, posPlayerX, posPlayerY);
	for (BolS2* bs : vecBS) bs->update(deltaTime, posPlayerX, posPlayerY);
}

void EnemyManager::render()
{
	for (Turret* t : vecTurret) t->render();
	for (TorRafaga* tr : vecTorRafaga) tr->render();
	for (Runner* r : vecRunner) r->render();
	for (Soldier* so : vecSoldier) so->render();
	for (Sniper* sn : vecSniper) sn->render();
	for (GreenSoldier* gs : vecGS) gs->render();
	for (TorS2* ts : vecTS) ts->render();
	for (BolS2* bs : vecBS) bs->render();
}
