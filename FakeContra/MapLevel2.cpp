#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapLevel2.h"
#include "Game.h"





enum MapLevel2Anims
{
	FASE_1, FASE_2, FASE_BOSS
};

void MapLevel2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	count1 = count2 = count3 = countBoss = 0;
	fase1 = true;
	fase2 = fase3 = fase4 = false;
	spritesheet.loadFromFile("images/lvl2_boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(0.20, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);


	sprite->setAnimationSpeed(FASE_1, 8);
	sprite->addKeyframe(FASE_1, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(FASE_2, 2);
	sprite->addKeyframe(FASE_2, glm::vec2(0.20f, 0.00f));
	sprite->addKeyframe(FASE_2, glm::vec2(0.40f, 0.00f));
	sprite->addKeyframe(FASE_2, glm::vec2(0.60f, 0.00f));

	sprite->setAnimationSpeed(FASE_BOSS, 2);
	sprite->addKeyframe(FASE_BOSS, glm::vec2(0.80f, 0.00f));




	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
}

void MapLevel2::update(int deltaTime, ShaderProgram& shaderProgram)
{
	sprite->update(deltaTime);
	//cout << EnemyManager::instance().getKills() << endl;
	if (count1 < 30 && fase1) {
		EnemyManager::instance().transition(false);
		sprite->changeAnimation(FASE_1);
		if (BulletManager::instance().isPlayerBulletInside(glm::vec2(225, 110), glm::vec2(167, 160), glm::vec2(0, 0)))	count1++; //count suma de 5 en 5 porque si
	}
	
	else if (count1 > 6 || EnemyManager::instance().getKills() >= EnemyManager::instance().getSize() && fase1) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
		fase1 = false;
		++count1;
		if (count1 > 95) {
			count1 = 0;
			fase2 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 3);
		}
	}
	else if (fase2) {
		EnemyManager::instance().transition(false);
		if (EnemyManager::instance().getKills() >= EnemyManager::instance().getSize()) {
			fase2 = false;
			count2 = 35;
		}
	}
	if (count2 > 6) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
		fase2 = false;
		++count2;
		if (count2 > 100) {
			count2 = 0;
			fase3 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 4);
		}
	}
	else if (fase3) {
		EnemyManager::instance().transition(false);
		if (EnemyManager::instance().getKills() >= EnemyManager::instance().getSize()) {
			fase3 = false;
			count3 = 35;
		}
	}
	if (count3 > 6) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
		fase3 = false;
		++count3;
		if (count3 > 120) {
			count3 = 0;
			fase4 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 5);
		}
	}
	else if (fase4) {
		EnemyManager::instance().transition(false);
		if (EnemyManager::instance().getKills() >= EnemyManager::instance().getSize()) {
			fase4 = false;
			count4 = 35;
		}
	}
	if (count4 > 6) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
		fase4 = false;
		++count4;
		if (count4 > 120) {
			count4 = 0;
			faseBoss = true;
			initBoss = true;
			if (sprite->animation() != FASE_BOSS)sprite->changeAnimation(FASE_BOSS);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 6);
			
		}
	}
	else if (faseBoss) {
		initBoss = false;
		//if (sprite->animation() != FASE_BOSS)sprite->changeAnimation(FASE_BOSS);
		EnemyManager::instance().isFaseBoss(true);
		EnemyManager::instance().transition(false);
		if (count1 < 5) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(155, 105), glm::vec2(78, 160), glm::vec2(0, 0)))	count1++;
		}
		if (count2 < 5) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(280, 105), glm::vec2(78, 160), glm::vec2(0, 0)))	count2++;
		}
		if (count3 < 5) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(400, 105), glm::vec2(78, 160), glm::vec2(0, 0)))	count3++;
		}
		if (count4 < 5) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(155, 210), glm::vec2(78, 160), glm::vec2(0, 0)))	count4++;
		}
		if (count5 < 5) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(280, 210), glm::vec2(78, 160), glm::vec2(0, 0)))	count5++;
		}
		if (count6 < 5) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(400, 210), glm::vec2(78, 160), glm::vec2(0, 0)))	count6++;
		}
	}
	if (countBoss > 6) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
		faseBoss = false;
		++countBoss;
		if (countBoss > 120) {
			countBoss = 0;
			faseEnd = true;
			if (sprite->animation() != FASE_BOSS)sprite->changeAnimation(FASE_BOSS);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 7);
		}
	}
}



void MapLevel2::render()
{
	sprite->render();
}

void MapLevel2::setPosition(const glm::vec2& pos)
{
	posMapLevel2 = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapLevel2.x), float(tileMapDispl.y + posMapLevel2.y)));
}

bool MapLevel2::isFaseBoss()
{
	return initBoss;
}




