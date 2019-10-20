#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerLevel2.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define WALK_STEP 2

#define STANDBOX glm::vec2(40.f, 67.f)
#define BENDBOX glm::vec2(40.f, 57.f)
#define JUMPBOX glm::vec2(35.f, 35.f)


enum PlayerLevel2Anims
{
	RUN_FORW, 

	STAND_NS, STAND_SH,

	MOVE_LEFT, MOVE_RIGHT, 

	JUMP_LEFT, JUMP_RIGHT,

	BEND_NS, BEND_SH,

	DIE,
};

void PlayerLevel2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	lastShoot = 0;
	isDead = false;

	boxPlayer = glm::vec2(30.0f, 30.0);

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	//STAND FORW RIGHT LEFT SHOOT NO SHOT
	sprite->setAnimationSpeed(STAND_NS, 8);
	sprite->addKeyframe(STAND_NS, glm::vec2(0.10f, 0.45f));
	sprite->setAnimationSpeed(STAND_SH, 8);
	sprite->addKeyframe(STAND_SH, glm::vec2(0.00f, 0.45f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.30f, 0.50f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.50f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.20f, 0.50f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.00f, 0.50f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.05f, 0.50f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.10f, 0.50f));

	//JUMP LEFT RIGHT
	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.55f, 0.10f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.50f, 0.10f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.45f, 0.10f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.40f, 0.10f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.00f, 0.10f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.05f, 0.10f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.10f, 0.10f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.15f, 0.10f));

	sprite->setAnimationSpeed(BEND_NS, 8);
	sprite->addKeyframe(BEND_NS, glm::vec2(0.15f, 0.45f));
	sprite->setAnimationSpeed(BEND_SH, 8);
	sprite->addKeyframe(BEND_SH, glm::vec2(0.05f, 0.45f));

	sprite->setAnimationSpeed(RUN_FORW, 8);
	sprite->addKeyframe(RUN_FORW, glm::vec2(0.20f, 0.45f));
	sprite->addKeyframe(RUN_FORW, glm::vec2(0.25f, 0.45f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.15f, 0.50f));



	sprite->changeAnimation(0);
	bDir = true;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void PlayerLevel2::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (!isDead) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			bDir = false;

			if (!bJumping) {
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
				setBox(STANDBOX);
				if (Game::instance().getKey(int('x'))) {
					doShoot(15.0, -80.0, 0.0, -1.0);
				}
			}

			posPlayer.x -= WALK_STEP;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += WALK_STEP;
				if (!bJumping) sprite->changeAnimation(STAND_NS);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			bDir = true;
			if (!bJumping) {
				if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
				setBox(STANDBOX);
				if (Game::instance().getKey(int('x'))) {
					doShoot(17.5, -80.0, 0.0, -1.0);
				}
				
			}

			posPlayer.x += WALK_STEP;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= WALK_STEP;
				if (!bJumping) sprite->changeAnimation(STAND_NS);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (!bJumping) {
				setBox(BENDBOX);
				if (Game::instance().getKey(int('x'))) {
					sprite->changeAnimation(BEND_SH);
					doShoot(20.0, -60.0, 0.0, -1.0);
				}
				else sprite->changeAnimation(BEND_NS);
			}

		}

		else
		{
			if (!bJumping) {
				setBox(STANDBOX);
				if (Game::instance().getKey(int('x'))) {
					sprite->changeAnimation(STAND_SH);
					doShoot(17.5, -80.0, 0.0, -1.0);
				}
				else sprite->changeAnimation(STAND_NS);
			}
		}

		if (bJumping) {
			setBox(JUMPBOX);
			if (bDir && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
			else if (!bDir && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);

			if (Game::instance().getKey(int('x'))) {
				doShoot(15.0, -30.0, 0.0, -1.0);
			}
			

			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
				sprite->changeAnimation(STAND_NS);
			}
			else
			{
				posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
			}
		}
		else{
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
			{
				//if(Game::instance().getSpecialKey(GLUT_KEY_UP))
				if (Game::instance().getKey(int('z')))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}
	}
	else {

		sprite->changeAnimation(DIE);

		posPlayer.y += FALL_STEP;
		map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		

	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void PlayerLevel2::render()
{
	sprite->render();
}

void PlayerLevel2::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PlayerLevel2::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 PlayerLevel2::getPosition()
{
	return posPlayer;
}

float PlayerLevel2::getPosX()
{
	//prova de canvi de branca
	return float(posPlayer.x);
}

float PlayerLevel2::getPosY()
{
	return float(posPlayer.y);
}

glm::vec2 PlayerLevel2::getBox()
{
	return boxPlayer;
}

void PlayerLevel2::setBox(glm::vec2 box)
{
	boxPlayer = box;
}

void PlayerLevel2::doShoot(float desplX, float desplY, float dirX, float dirY) {
	if (lastShoot == 0) {
		glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
		glm::vec2 dir = glm::vec2(dirX, dirY);
		BulletManager::instance().createBullet(pos, dir, 4, 1);
		lastShoot = Time::instance().getMili();
	}
	else {
		if (Time::instance().isAbleToShoot(lastShoot)) {
			glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			BulletManager::instance().createBullet(pos, dir, 4, 1);
			lastShoot = Time::instance().getMili();
		}
	}
}

void PlayerLevel2::setDeadState(bool dead) {
	isDead = dead;
}