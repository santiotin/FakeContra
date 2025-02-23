#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapLevel2.h"
#include "Game.h"





enum MapLevel2Anims
{
	FASE_1, FASE_2, FASE_BOSS,STAGE
};

void MapLevel2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	count1 = count2 = count3 = countBoss = 0;
	fase1 = true;
	fase2 = fase3 = fase4 = false;
	spritesheet.loadFromFile("images/stage2_boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(0.333, 0.50), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(STAGE, 8);
	sprite->addKeyframe(STAGE, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(FASE_1, 8);
	sprite->addKeyframe(FASE_1, glm::vec2(0.333f, 0.00f));

	sprite->setAnimationSpeed(FASE_2, 2);
	sprite->addKeyframe(FASE_2, glm::vec2(0.666f, 0.00f));
	sprite->addKeyframe(FASE_2, glm::vec2(0.00f, 0.50f));
	sprite->addKeyframe(FASE_2, glm::vec2(0.333f, 0.50f));

	sprite->setAnimationSpeed(FASE_BOSS, 2);
	sprite->addKeyframe(FASE_BOSS, glm::vec2(0.666f, 0.50f));

	segs = Time::instance().getMili();
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
}

void MapLevel2::update(int deltaTime, ShaderProgram& shaderProgram)
{
	EnemyManager::instance().isFaseBoss(false);
	sprite->update(deltaTime);
	if (Time::instance().getMili() - segs < 2000) {
		if (sprite->animation() != STAGE) sprite->changeAnimation(STAGE);
	}
	else {
		if (count1 < 30 && fase1) {
			EnemyManager::instance().transition(false);
			sprite->changeAnimation(FASE_1);
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(225, 110), glm::vec2(167, 160), glm::vec2(0, 0)))	count1++; //count suma de 5 en 5 porque si
		}

		else if (count1 > 6 || EnemyManager::instance().getKills() >= EnemyManager::instance().getSize() && fase1) {
			EnemyManager::instance().transition(true);
			EnemyManager::instance().cleanEnemies();
			BulletManager::instance().cleanBullets();
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
			BulletManager::instance().cleanBullets();
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
			BulletManager::instance().cleanBullets();
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
			BulletManager::instance().cleanBullets();
			if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
			fase4 = false;
			++count4;
			if (count4 > 100) {
				count4 = 0;
				faseBoss = true;
				initBoss = true;
				/*BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
				EnemyManager::instance().init(map, shaderProgram, 6);*/

			}
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




