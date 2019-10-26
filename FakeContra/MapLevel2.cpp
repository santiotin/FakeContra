#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapLevel2.h"
#include "Game.h"





enum MapLevel2Anims
{
	FASE_1, FASE_2
};

void MapLevel2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	count1 = count2 = count3 = 0;
	fase1 = true;
	fase2 = fase3 = fase4 = false;
	spritesheet.loadFromFile("images/lvl2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(0.25, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);


	sprite->setAnimationSpeed(FASE_1, 8);
	sprite->addKeyframe(FASE_1, glm::vec2(0.00f, 0.00f));
	sprite->setAnimationSpeed(FASE_2, 2);
	sprite->addKeyframe(FASE_2, glm::vec2(0.25f, 0.00f));
	sprite->addKeyframe(FASE_2, glm::vec2(0.50f, 0.00f));
	sprite->addKeyframe(FASE_2, glm::vec2(0.75f, 0.00f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
}

void MapLevel2::update(int deltaTime, ShaderProgram& shaderProgram)
{
	sprite->update(deltaTime);
	//cout << EnemyManager::instance().getKills() << endl;
	if (count1 < 35 && fase1) {
		cout << "ESTOY FASE 1" << endl;
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
		if (count1 > 120) {
			count1 = 0;
			fase2 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 3);
		}
	}
	else if (fase2) {
		cout << "ESTOY FASE 2 " << endl;
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
		cout << "COUNT2 = " << count2 << endl;
		++count2;
		if (count2 > 120) {
			count2 = 0;
			fase3 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 4);
		}
	}
	else if (fase3) {
		cout << "ESTOY FASE 3 " << endl;
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
		//cout << "COUNT3 = " << count3 << endl;
		++count3;
		cout << "NUMERO DE ENEMIGOS ANTES FASE FINAL   " << EnemyManager::instance().getSize() << endl;
		if (count3 > 120) {
			count3 = 0;
			fase4 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 5);
		}
	}
	else if (fase4) {
		cout << "ESTOY FASE 4 " << endl;
		cout << "NUMERO DE ENEMIGOS   " << EnemyManager::instance().getSize() << endl;
		EnemyManager::instance().transition(false);
		if (EnemyManager::instance().getKills() >= EnemyManager::instance().getSize()) {
			fase4 = false;
			countBoss = 35;
		}
	}
	if (countBoss > 6) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_2) sprite->changeAnimation(FASE_2);
		fase3 = false;
		cout << "COUNT_BOSS = " << countBoss << endl;
		++countBoss;
		if (countBoss > 120) {
			countBoss = 0;
			fase4 = true;
			if (sprite->animation() != FASE_1)sprite->changeAnimation(FASE_1);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 5);
		}
	}
}
	
	/*void MapLevel2::update(int deltaTime, float posPlayerX, float posPlayerY)
	{
		sprite->update(deltaTime);

		if (count < 7 ) {
				sprite->changeAnimation(FASE_1);
				if (BulletManager::instance().isBulletInside(glm::vec2(225, 160), glm::vec2(167, 160))) ++count;
		}
		else {
			if (sprite->animation() != FASE_2)sprite->changeAnimation(FASE_2);
			count++;
		}
	}*/


void MapLevel2::render()
{
	sprite->render();
}

void MapLevel2::setPosition(const glm::vec2& pos)
{
	posMapLevel2 = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapLevel2.x), float(tileMapDispl.y + posMapLevel2.y)));
}




