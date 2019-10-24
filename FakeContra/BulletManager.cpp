#include "BulletManager.h"
#include <iostream>
#include <cmath>
#include <vector> 
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <windows.h>



void BulletManager::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram){
	sh = shaderProgram;
	tileMapDispl = tileMapPos;
	if (!playerBullets.empty())  playerBullets.clear();
	if (!enemyBullets.empty()) enemyBullets.clear();

	//prueba de collision
	glm::vec2 fakePos = glm::vec2(400.0, 80.0);
	glm::vec2 fakeDir = glm::vec2(-1.0, 0);
	createEnemyBullet(fakePos, fakeDir, 2.0, 0);

}

void BulletManager::update(int deltaTime, float posPlayerX) {
	float minWidth = posPlayerX - (SCREEN_WIDTH - 1)/1.1;
	float maxWidth = posPlayerX + (SCREEN_WIDTH - 1)/1.1;

	for (int i = 0; i < playerBullets.size(); i++) {
		Bullet* bullet = playerBullets[i];
		if (bullet != NULL) {
			if (bullet->getPosition().x > maxWidth || bullet->getPosition().x < minWidth) {
				playerBullets[i] = NULL;
				//OutputDebugStringA("Dead");
			}
			else if(bullet->isDead()) playerBullets[i] = NULL;

			else bullet->update(deltaTime);
		}
		
	}

	for (int i = 0; i < enemyBullets.size(); i++) {
		Bullet* bullet = enemyBullets[i];
		if (bullet != NULL) {
			if (bullet->getPosition().x > maxWidth || bullet->getPosition().x < minWidth) {
				enemyBullets[i] = NULL;
				//OutputDebugStringA("Dead");
			}
			else if (bullet->isDead()) enemyBullets[i] = NULL;

			else bullet->update(deltaTime);
		}

	}
}

void BulletManager::render() {
	for (Bullet *bullet : playerBullets) {
		if (bullet != NULL) {
			bullet->render();
		}
	}

	for (Bullet* bullet : enemyBullets) {
		if (bullet != NULL) {
			bullet->render();
		}
	}
}

void BulletManager::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BulletManager::createPlayerBullet(glm::vec2 posBullet, glm::vec2 dirBullet, float speed, int type) {
	Bullet *bullet;
	bullet = new Bullet();
	bullet->init(tileMapDispl, sh, posBullet, dirBullet, speed, type);
	playerBullets.push_back(bullet);

}
void BulletManager::createEnemyBullet(glm::vec2 posBullet, glm::vec2 dirBullet, float speed, int type) {

	Bullet* bullet;
	bullet = new Bullet();
	bullet->init(tileMapDispl, sh, posBullet, dirBullet, speed, type);
	enemyBullets.push_back(bullet);

}

bool BulletManager::isPlayerBulletInside(glm::vec2 pos, glm::vec2 box) {

	for (int i = 0; i < playerBullets.size(); i++) {
		Bullet* bullet = playerBullets[i];
		if (bullet != NULL) {
			if (bullet->getPosition().x > pos.x&& bullet->getPosition().x < (pos.x + box.x)) {
				if (bullet->getPosition().y < (pos.y ) && bullet->getPosition().y >(pos.y - box.y)) {
					OutputDebugStringA("DEAD/n");
					bullet->setDead();
					return true;
				}
			}
		}

	}
	return false;
}
bool BulletManager::isEnemyBulletInside(glm::vec2 pos, glm::vec2 box) {

	for (int i = 0; i < enemyBullets.size(); i++) {
		Bullet* bullet = enemyBullets[i];
		if (bullet != NULL) {
			if (bullet->getPosition().x > pos.x&& bullet->getPosition().x < (pos.x + box.x)) {
				if (bullet->getPosition().y < (pos.y) && bullet->getPosition().y >(pos.y - box.y)) {
					OutputDebugStringA("DEAD/n");
					bullet->setDead();
					return true;
				}
			}
		}

	}
	return false;
}
