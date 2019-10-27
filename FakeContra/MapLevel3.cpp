#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapLevel3.h"
#include "Game.h"





enum MapLevel3Anims
{
	FASE_BOSS,TOR_ROTA, FASE_END
};

void MapLevel3::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	count1 = count2 = count3 = count4 = count5 = count6 = 0;
	fase1 = true;
	fase2 = fase3 = fase4 = false;
	spritesheet.loadFromFile("images/boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.00, 1.00), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(FASE_BOSS, 2);
	sprite->addKeyframe(FASE_BOSS, glm::vec2(0.00f, 0.00f));

	EnemyManager::instance().cleanEnemies();
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
}

void MapLevel3::update(int deltaTime, ShaderProgram& shaderProgram)
{
	sprite->update(deltaTime);
	if (sprite->animation() != FASE_BOSS)sprite->changeAnimation(FASE_BOSS);
	EnemyManager::instance().transition(false);
	EnemyManager::instance().isFaseBoss(true);
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




