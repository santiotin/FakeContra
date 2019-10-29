#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapLevel3.h"
#include "Game.h"





enum MapLevel3Anims
{
	FASE_BOSS,FASE_INI, FASE_END
};

void MapLevel3::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	count1 = count2 = count3 = count4 = count5 = count6 = 0;
	fase1 = true;
	fase2 = fase3 = fase4 = done = win = end =false;
	spritesheet.loadFromFile("images/boss_final.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(0.20, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(FASE_INI, 2);
	sprite->addKeyframe(FASE_INI, glm::vec2(0.00f, 0.00f));

	sprite->setAnimationSpeed(FASE_BOSS, 8);
	sprite->addKeyframe(FASE_BOSS, glm::vec2(0.20f, 0.00f));
	sprite->addKeyframe(FASE_BOSS, glm::vec2(0.40f, 0.00f));
	sprite->addKeyframe(FASE_BOSS, glm::vec2(0.60f, 0.00f));

	sprite->setAnimationSpeed(FASE_END, 2);
	sprite->addKeyframe(FASE_END, glm::vec2(0.80f, 0.00f));

	EnemyManager::instance().cleanEnemies();
	BulletManager::instance().cleanBullets();
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

	segs = Time::instance().getMili();
	sprite->changeAnimation(0);
}

void MapLevel3::update(int deltaTime, ShaderProgram& shaderProgram)
{
	sprite->update(deltaTime);
	if (Time::instance().getMili() - segs < 2000) {
		EnemyManager::instance().transition(true);
		if (sprite->animation() != FASE_INI) sprite->changeAnimation(FASE_INI);
	}
	else {
		if (!done) {
			done = true;
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 6);
		}
		if (sprite->animation() != FASE_BOSS)sprite->changeAnimation(FASE_BOSS);
		EnemyManager::instance().transition(false);
		EnemyManager::instance().isFaseBoss(true);
		if (count1 < 10) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(155, 105), glm::vec2(78, 160), glm::vec2(0, 0)))	count1++;
		}
		if (count2 < 10) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(280, 105), glm::vec2(78, 160), glm::vec2(0, 0)))	count2++;
		}
		if (count3 < 10) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(400, 105), glm::vec2(78, 160), glm::vec2(0, 0)))	count3++;
		}
		if (count4 < 10) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(155, 210), glm::vec2(78, 160), glm::vec2(0, 0)))	count4++;
		}
		if (count5 < 10) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(280, 210), glm::vec2(78, 160), glm::vec2(0, 0)))	count5++;
		}
		if (count6 < 10) { //dos vidas son count1 < 5
			if (BulletManager::instance().isPlayerBulletInside(glm::vec2(400, 210), glm::vec2(78, 160), glm::vec2(0, 0)))	count6++;
		}
		if (count1 < 10 || count2 < 10 || count3 < 10 || count4 < 10 || count5 < 10 || count6 < 10 ) {
			BulletManager::instance().isPlayerBulletInside(glm::vec2(160, 50), glm::vec2(350, 160), glm::vec2(0, 0));
		}
		if (EnemyManager::instance().getKills() > 6 && !end) {
			BulletManager::instance().cleanBullets();
			end = true;
			segswin = Time::instance().getMili();
			Music::instance().win();
		}
		if (Time::instance().getMili() - segswin < 5100) {
			if (sprite->animation() != FASE_END)sprite->changeAnimation(FASE_END);
			if (Time::instance().getMili() - segswin > 5000) {
				win = true;
			}
		}
	}
	
	
	/*if (count1 < 35 && faseBoss) {
		EnemyManager::instance().transition(false);
		sprite->changeAnimation(FASE_BOSS);
		if (BulletManager::instance().isPlayerBulletInside(glm::vec2(225, 110), glm::vec2(167, 160), glm::vec2(0, 0)))	count1++; //count suma de 5 en 5 porque si
	}

	else if (count1 > 6 || EnemyManager::instance().getKills() >= EnemyManager::instance().getSize() && faseBoss) {
		EnemyManager::instance().transition(true);
		EnemyManager::instance().cleanEnemies();
		if (sprite->animation() != FASE_END) sprite->changeAnimation(FASE_END);
		fase1 = false;
		++count1;
		if (count1 > 120) {
			count1 = 0;
			fase2 = true;
			if (sprite->animation() != FASE_BOSS)sprite->changeAnimation(FASE_END);
			BulletManager::instance().init(glm::ivec2(0, 0), shaderProgram);
			EnemyManager::instance().init(map, shaderProgram, 3);
		}
	}*/
}



void MapLevel3::render()
{
	sprite->render();
}

void MapLevel3::setPosition(const glm::vec2& pos)
{
	posMapLevel2 = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapLevel2.x), float(tileMapDispl.y + posMapLevel2.y)));
}

bool MapLevel3::isFaseBoss()
{
	return faseBoss;
}
bool MapLevel3::goMenu()
{
	return win;
}




