#include "Enemy.h"


void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

}

void Enemy::update(int deltaTime, float posPlayerX, float posPlayerY, bool isDead) {

}
void Enemy::render() {

}

void Enemy::setTileMap(TileMap* tileMap) {

}

void Enemy::setPosition(const glm::vec2& pos) {

}

glm::vec2 Enemy::getPosition() {
	return glm::vec2(-1.0, -1.0);
}

glm::vec2 Enemy::getBoxCollider() {
	return glm::vec2(-1.0, -1.0);
}

glm::vec2 Enemy::getStartP() {
	return glm::vec2(-1.0, -1.0);
}