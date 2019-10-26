#include "BulletManager.h"
#include <iostream>
#include <cmath>
#include <vector> 
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <windows.h>

#define bulletOffset 86

void BulletManager::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram){
	sh = shaderProgram;
	tileMapDispl = tileMapPos;

	if (!playerBullets.empty())  playerBullets.clear();
	if (!enemyBullets.empty()) enemyBullets.clear();

}

void BulletManager::update(int deltaTime, float posPlayerX, int level) {

	for (int i = 0; i < playerBullets.size(); i++) {
		Bullet* bullet = playerBullets[i];
		bool outside;
		if (bullet != NULL) {
			if (level == 1) {
				outside = isLevel1BulletOutside(bullet->getPosition(), posPlayerX);
			}else {
				outside = isLevel2BulletOutside(bullet->getPosition(), posPlayerX);
			}

			if (outside) {
				playerBullets[i] = NULL;
				//OutputDebugStringA("Dead");
			}
			else if(bullet->isDead()) playerBullets[i] = NULL;

			else bullet->update(deltaTime);
		}
		
	}

	for (int i = 0; i < enemyBullets.size(); i++) {
		Bullet* bullet = enemyBullets[i];
		bool outside;
		if (bullet != NULL) {
			if (level == 1) {
				outside = isLevel1BulletOutside(bullet->getPosition(), posPlayerX);
			}
			else {
				outside = isLevel2BulletOutside(bullet->getPosition(), posPlayerX);
			}

			if (outside) {
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

bool BulletManager::isPlayerBulletInside(glm::vec2 pos, glm::vec2 box, glm::vec2 startP) {

	for (int i = 0; i < playerBullets.size(); i++) {
		Bullet* bullet = playerBullets[i];
		if (bullet != NULL) {
			if (hitBox(bullet->getPosition(), pos, box, startP)) {
				OutputDebugStringA("DEAD/n");
				bullet->setDead();
				return true;
			}
		}

	}
	return false;
}
bool BulletManager::isEnemyBulletInside(glm::vec2 pos, glm::vec2 box, glm::vec2 startP) {

	for (int i = 0; i < enemyBullets.size(); i++) {
		Bullet* bullet = enemyBullets[i];
		if (bullet != NULL) {
			if (hitBox(bullet->getPosition(), pos, box, startP)) {
				OutputDebugStringA("DEAD/n");
				bullet->setDead();
				return true;
			}
		}

	}
	return false;
}

bool BulletManager::hitBox(glm::vec2 bulletPos, glm::vec2 entityPos, glm::vec2 entityBox, glm::vec2 entityStartP) {
	if (bulletPos.x > entityPos.x && bulletPos.x < (entityPos.x + entityBox.x)) {
		if ((bulletPos.y + bulletOffset) > entityPos.y+entityStartP.y && (bulletPos.y + bulletOffset) < (entityPos.y+ entityStartP.y+ entityBox.y)) {
			return true;
		}
		else return false;
	}
	else return false;
	
}

bool BulletManager::isLevel1BulletOutside(glm::vec2 posBullet, float posPlayerX) {
	float minWidth = posPlayerX - (SCREEN_WIDTH - 1) / 1.1;
	float maxWidth = posPlayerX + (SCREEN_WIDTH - 1) / 1.1;

	if (posBullet.x > maxWidth || posBullet.x < minWidth) {
		return true;
	}
	else if (posBullet.y < -10.0 || posBullet.y > SCREEN_HEIGHT + 10.0) {
		return true;
	}
	else return false;
}
bool BulletManager::isLevel2BulletOutside(glm::vec2 posBullet, float posPlayerX) {
	if (posBullet.x > SCREEN_WIDTH + 10.0 || posBullet.x < -10.0) {
		return true;
	}
	else if (posBullet.y < SCREEN_HEIGHT * 0.30 || posBullet.y > SCREEN_HEIGHT) {
		//OutputDebugStringA("Bullet OUTSIDE");
		return true;
	}
	else return false;
}
