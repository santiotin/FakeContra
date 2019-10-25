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
	if (!bullets.empty())  bullets.clear();

	//prueba de collision
	//glm::vec2 fakePos = glm::vec2(400.0, 80.0);
	//glm::vec2 fakeDir = glm::vec2(-1.0, 0);
	//createBullet(fakePos, fakeDir, 2.0, 0);

}

void BulletManager::update(int deltaTime, float posPlayerX) {
	float minWidth = posPlayerX - (SCREEN_WIDTH - 1)/1.1;
	float maxWidth = posPlayerX + (SCREEN_WIDTH - 1)/1.1;

	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
		if (bullet != NULL) {
			if (bullet->getPosition().x > maxWidth || bullet->getPosition().x < minWidth) {
				bullets[i] = NULL;
				//OutputDebugStringA("Dead");
			}
			else if(bullet->isDead()) bullets[i] = NULL;

			else bullet->update(deltaTime);
		}
		
	}
}

void BulletManager::render() {
	for (Bullet *bullet : bullets) {
		if (bullet != NULL) {
			bullet->render();
		}
		
	}
}

void BulletManager::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BulletManager::createBullet(glm::vec2 posBullet, glm::vec2 dirBullet, float speed, int type) {
	Bullet *bullet;
	bullet = new Bullet();
	bullet->init(tileMapDispl, sh, posBullet, dirBullet, speed, type);
	bullets.push_back(bullet);

}

bool BulletManager::isBulletInside(glm::vec2 pos, glm::vec2 box) {

	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
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
