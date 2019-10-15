#include "BulletManager.h"
#include <iostream>
#include <cmath>
#include <vector> 
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"



void BulletManager::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram){
	sh = shaderProgram;
	tileMapDispl = tileMapPos;

}

void BulletManager::update(int deltaTime) {
	for (Bullet *bullet : bullets) {
		bullet->update(deltaTime);
	}
}

void BulletManager::render() {
	for (Bullet *bullet : bullets) {
		bullet->render();
	}
}

void BulletManager::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BulletManager::createBullet(float px, float py, float dx, float dy) {
	Bullet *bullet;
	bullet = new Bullet();
	bullet->init(tileMapDispl, sh, dx, dy);
	bullet->setPosition(px,py);

	bullets.push_back(bullet);

}
