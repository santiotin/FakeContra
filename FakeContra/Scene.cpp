#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Game.h"


//commit para branch


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 3
#define INIT_PLAYER_Y_TILES 1

#define INIT_PLAYER2_X_TILES 9
#define INIT_PLAYER2_X_TILES 10
#define INIT_PLAYER2_Y_TILES 10.5

#define INIT_LVL2_X_TILES 0.0
#define INIT_LVL2_Y_TILES 1.4

#define DEAD_TIME 110

enum SceneModes
{
	MENU, LEVEL_1, LEVEL_2, LEVEL_3
};


Scene::Scene()
{
	map = NULL;
	player = NULL;
	playerLevel2 = NULL;
	menu = NULL;
	mode = MENU;

}

Scene::~Scene()
{
	if(map != NULL)
		delete map;

	if(player != NULL)
		delete player;

}


void Scene::init()
{
	initShaders();
	
	if (getMode() == MENU) {
		map = TileMap::createTileMap("levels/fakelevel01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		menu = new Menu();
		menu->init(glm::ivec2(SCREEN_X - 640, SCREEN_Y), texProgram);
	}
	else if (getMode() == LEVEL_1) {
		map = TileMap::createTileMap("levels/fakelevel01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

		BulletManager::instance().init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		EnemyManager::instance().init(map, texProgram, 1);

		icon = new LifeIcon();
		icon->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES * map->getTileSize()), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setTileMap(map);

	}
	else if (getMode() == LEVEL_2) {
		map = TileMap::createTileMap("levels/fakelevel01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl2 = new MapLevel2();
		lvl2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl2->setPosition(glm::vec2((INIT_LVL2_X_TILES * map->getTileSize()), INIT_LVL2_Y_TILES * map->getTileSize()));

		BulletManager::instance().init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		EnemyManager::instance().init(map, texProgram, 2);

		playerLevel2 = new PlayerLevel2();
		playerLevel2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		playerLevel2->setPosition(glm::vec2((INIT_PLAYER2_X_TILES * map->getTileSize()), INIT_PLAYER2_Y_TILES * map->getTileSize()));
		playerLevel2->setTileMap(map);
	}


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1) , float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	if (getMode() == MENU) {
		menu->update(deltaTime);
		if (Game::instance().getKey(13)) {
			setMode(LEVEL_1);
			init();
		}
	}

	else if(getMode() == LEVEL_1){

		if (player->getDeadState() && player->getLifes() > 0 && player->getDeadTime() > DEAD_TIME) {
			glm::vec2 aux = player->getPosition();
			aux.y = 80.0;
			player->setDeadState(false);
			player->setPosition(aux);
		}
		else if (player->getDeadState() && player->getLifes() > 0 && player->getDeadTime() < DEAD_TIME) {
			//do nothing
		}
		else if (player->getDeadState() && player->getLifes() == 0) {
			setMode(MENU);
			init();
		}
		else {
			if (BulletManager::instance().isEnemyBulletInside(player->getPosition(), player->getBox(), player->getStartP()) ||
				EnemyManager::instance().isEnemyInside(player->getPosition(), player->getBox())) {
				//player->setDeadState(true);
			}
		}

		player->update(deltaTime);

		EnemyManager::instance().update(deltaTime, player->getPosX(), player->getPosY());
		BulletManager::instance().update(deltaTime, player->getPosX(), 1);

		icon->changeLife(player->getLifes());
		icon->update(deltaTime);
	}

	else if (getMode() == LEVEL_2) {
		playerLevel2->update(deltaTime);

		//lvl2->update(deltaTime, playerLevel2->getPosX(), playerLevel2->getPosY());
		lvl2->update(deltaTime, texProgram);
		if (BulletManager::instance().isEnemyBulletInside(playerLevel2->getPosition(), playerLevel2->getBox(), playerLevel2->getStartP())) {
			playerLevel2->setDeadState(true);
		}

		EnemyManager::instance().update(deltaTime, playerLevel2->getPosX(), playerLevel2->getPosY());
		BulletManager::instance().update(deltaTime, playerLevel2->getPosX(), 2);
	}


	if (Game::instance().getSpecialKey(GLUT_KEY_F9)) {
		setMode(MENU);
		init();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_F1)) {
		setMode(LEVEL_1);
		init();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_F2)) {
		setMode(LEVEL_2);
		init();
	}

	updateCamera();
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

	if (getMode() == MENU) {
		menu->render();
	}
	else if (getMode() == LEVEL_1) {
		EnemyManager::instance().render();
		player->render();
		BulletManager::instance().render();
		icon->render();
	}
	else if (getMode() == LEVEL_2) {
		lvl2->render();
		EnemyManager::instance().render();
		playerLevel2->render();
		BulletManager::instance().render();

	}

	

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

void Scene::updateCamera() {
	if (getMode() == MENU) {
		projection = glm::ortho(float(-SCREEN_WIDTH + 1), 0.f, float(SCREEN_HEIGHT - 1), 0.f);
	}
	else if (getMode() == LEVEL_1) {
		if (player->getPosX() < ((SCREEN_WIDTH - 1) / 2)) {
			projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
			
			icon->setPosition(glm::vec2(30.0, 0.0));
		}
		else {
			projection = glm::ortho(player->getPosX() - ((SCREEN_WIDTH - 1) / 2), player->getPosX() + ((SCREEN_WIDTH - 1) / 2), float(SCREEN_HEIGHT - 1), 0.f);
			
			glm::vec2 aux = glm::vec2(player->getPosX() + 30.0 - ((SCREEN_WIDTH - 1) / 2), 0.0f);
			icon->setPosition(aux);
		}
	}
	else if (getMode() == LEVEL_2) {

		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		
	}
	
}

int Scene::getMode() {
	return mode;
}

void Scene::setMode(int m) {
	mode = m;
}

int Scene::getEnum(int s) {
	switch (s) {
		case 0:
			return MENU;
			break;
		case 1:
			return LEVEL_1;
			break;
		case 2:
			return LEVEL_2;
			break;
		case 3:
			return LEVEL_3;
			break;
	}
}



