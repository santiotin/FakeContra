#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 3

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
#define INIT_TORRAFAGA2_X_TILES 174
#define INIT_TORRAFAGA2_Y_TILES 8.4
#define INIT_TORRAFAGA3_X_TILES 128
#define INIT_TORRAFAGA3_Y_TILES 10.4


Scene::Scene()
{
	map = NULL;
	player = NULL;
	turret1 = NULL;
	torrafaga1 = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;

	if(player != NULL)
		delete player;

	if (turret1 != NULL)
		delete turret1;
	if (turret2 != NULL)
		delete turret1;
	if (turret3 != NULL)
		delete turret1;
	if (turret4 != NULL)
		delete turret1;
	if (turret5 != NULL)
		delete turret1;
	if (turret6 != NULL)
		delete turret1;

	if (torrafaga1 != NULL)
		delete torrafaga1;
	if (torrafaga2 != NULL)
		delete torrafaga1;
	if (torrafaga3 != NULL)
		delete torrafaga1;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/fakelevel01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2((INIT_PLAYER_X_TILES *map->getTileSize()) - 208, INIT_PLAYER_Y_TILES *map->getTileSize()));
	player->setTileMap(map);

	turret1 = new Turret();
	turret1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	turret1->setPosition(glm::vec2((INIT_TURRET1_X_TILES * map->getTileSize()), INIT_TURRET1_Y_TILES * map->getTileSize()));
	turret1->setTileMap(map);
	turret2 = new Turret();
	turret2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	turret2->setPosition(glm::vec2((INIT_TURRET2_X_TILES * map->getTileSize()), INIT_TURRET2_Y_TILES * map->getTileSize()));
	turret2->setTileMap(map);
	turret3 = new Turret();
	turret3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	turret3->setPosition(glm::vec2((INIT_TURRET3_X_TILES * map->getTileSize()), INIT_TURRET3_Y_TILES * map->getTileSize()));
	turret3->setTileMap(map);
	turret4 = new Turret();
	turret4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	turret4->setPosition(glm::vec2((INIT_TURRET4_X_TILES * map->getTileSize()), INIT_TURRET4_Y_TILES * map->getTileSize()));
	turret4->setTileMap(map);
	turret5 = new Turret();
	turret5->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	turret5->setPosition(glm::vec2((INIT_TURRET5_X_TILES * map->getTileSize()), INIT_TURRET5_Y_TILES * map->getTileSize()));
	turret5->setTileMap(map);
	turret6 = new Turret();
	turret6->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	turret6->setPosition(glm::vec2((INIT_TURRET6_X_TILES * map->getTileSize()), INIT_TURRET6_Y_TILES * map->getTileSize()));
	turret6->setTileMap(map);

	torrafaga1 = new TorRafaga();
	torrafaga1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	torrafaga1->setPosition(glm::vec2((INIT_TORRAFAGA1_X_TILES * map->getTileSize()), INIT_TORRAFAGA1_Y_TILES * map->getTileSize()));
	torrafaga1->setTileMap(map);
	torrafaga2 = new TorRafaga();
	torrafaga2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	torrafaga2->setPosition(glm::vec2((INIT_TORRAFAGA2_X_TILES * map->getTileSize()), INIT_TORRAFAGA2_Y_TILES * map->getTileSize()));
	torrafaga2->setTileMap(map);
	torrafaga3 = new TorRafaga();
	torrafaga3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	torrafaga3->setPosition(glm::vec2((INIT_TORRAFAGA3_X_TILES * map->getTileSize()), INIT_TORRAFAGA3_Y_TILES * map->getTileSize()));
	torrafaga3->setTileMap(map);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1) , float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime);

	turret1->update(deltaTime,player->getPosX());
	turret2->update(deltaTime,player->getPosX());
	turret3->update(deltaTime, player->getPosX());
	turret4->update(deltaTime, player->getPosX());
	turret5->update(deltaTime, player->getPosX());
	turret6->update(deltaTime, player->getPosX());

	torrafaga1->update(deltaTime, player->getPosX());
	torrafaga2->update(deltaTime, player->getPosX());
	torrafaga3->update(deltaTime, player->getPosX());
	
	projection = glm::ortho(player->getPosX() - ((SCREEN_WIDTH - 1) / 2), player->getPosX() + ((SCREEN_WIDTH-1)/2), float(SCREEN_HEIGHT - 1), 0.f);
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();

	player->render();

	turret1->render();
	turret2->render();
	turret3->render();
	turret4->render();
	turret5->render();
	turret6->render();

	torrafaga1->render();
	torrafaga2->render();
	torrafaga3->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



