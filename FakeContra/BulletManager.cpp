#include "BulletManager.h"
#include <iostream>
#include <cmath>
#include <vector> 
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
//#include <windows.h>



void BulletManager::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram){
	sh = shaderProgram;
	tileMapDispl = tileMapPos;

}

void BulletManager::update(int deltaTime, float posPlayerX) {
	float minWidth = posPlayerX - (SCREEN_WIDTH - 1);
	float maxWidth = posPlayerX + (SCREEN_WIDTH - 1);

	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
		if (bullet != NULL) {
			if (bullet->getPosition().x > maxWidth || bullet->getPosition().x < minWidth) {
				bullets[i] = NULL;
				//OutputDebugStringA("Dead");
			}
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

void BulletManager::createBullet(glm::vec2 posBullet, glm::vec2 dirBullet, float speed) {
	Bullet *bullet;
	bullet = new Bullet();
	bullet->init(tileMapDispl, sh, posBullet, dirBullet, speed);
	bullets.push_back(bullet);

}

bool BulletManager::isBulletInside(float bottomLeftX, float bottomRightX, float bottomLeftY, float topRightY) {
	for (Bullet* bullet : bullets) {
		if (bullet != NULL) {
			if (bullet->getPosition().x > bottomLeftX&& bullet->getPosition().x < bottomRightX) {
				if (bullet->getPosition().x > bottomLeftY&& bullet->getPosition().y < topRightY) {
					return true;
				}
			}
		}
		
	}

	return false;
}
