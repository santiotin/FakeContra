#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerLevel2.h"
#include "Game.h"

//prueba rama nueva de la ultima semana

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define WALK_STEP 2

#define STANDBOX glm::vec2(40.f, 70.f)
#define BENDBOX glm::vec2(40.f, 60.f)
#define JUMPBOX glm::vec2(35.f, 35.f)

#define STANDSTARTP glm::vec2(0.f, 20.f)
#define BENDSTARTP glm::vec2(0.f, 40.f)
#define JUMPSTARTP glm::vec2(0.f, 60.f)


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

	if (EnemyManager::instance().isBoss()) {
		posxmin = 70;
		posxmax = 540;
	}
	else {
		posxmin = 85;
		posxmax = 500;
	}

	lifes = 3;
	deadTime = 0;

	boxPlayer = glm::vec2(35.0f, 35.0);

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
	if (EnemyManager::instance().isTrans()) {
		if (sprite->animation() != RUN_FORW) sprite->changeAnimation(RUN_FORW);
	}
	else {
		if (!isDead) {
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && posPlayer.x > posxmin) {
				bDir = false;

				if (!bJumping) {
					if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
					setBox(STANDBOX);
					if (Game::instance().getKey(int('x'))) {
						doShoot(15.0, -90.0, 0.0, -1.0);
					}
				}

				posPlayer.x -= WALK_STEP;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x += WALK_STEP;
					if (!bJumping) sprite->changeAnimation(STAND_NS);
				}
			}

			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && posPlayer.x < posxmax) {
				bDir = true;
				if (!bJumping) {
					if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
					setBox(STANDBOX);
					if (Game::instance().getKey(int('x'))) {
						doShoot(17.5, -90.0, 0.0, -1.0);
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
						doShoot(20.0, -70.0, 0.0, -1.0);
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
						doShoot(17.5, -90.0, 0.0, -1.0);
					}
					else sprite->changeAnimation(STAND_NS);
				}
			}

			if (bJumping) {
				setBox(JUMPBOX);
				if (bDir && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
				else if (!bDir && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);

				if (Game::instance().getKey(int('x'))) {
					doShoot(15.0, -50.0, 0.0, -1.0);
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
				}
			}
			else {

				//if(Game::instance().getSpecialKey(GLUT_KEY_UP))
				if (Game::instance().getKey(int('z')))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}

			}
		}
		else {
			deadTime++;
			sprite->changeAnimation(DIE);
			if (posPlayer.y < 336) posPlayer.y = posPlayer.y + 4;
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
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

glm::vec2 PlayerLevel2::getStartP() {
	if (getBox().x == STANDBOX.x && getBox().y == STANDBOX.y) return STANDSTARTP;
	else if (getBox().x == BENDBOX.x && getBox().y == BENDBOX.y) return BENDSTARTP;
	else if (getBox().x == JUMPBOX.x && getBox().y == JUMPBOX.y) return JUMPSTARTP;

	return STANDSTARTP;
}

void PlayerLevel2::setStartP(glm::vec2 start) {
	startP = start;
}

void PlayerLevel2::setBox(glm::vec2 box)
{
	boxPlayer = box;
}

void PlayerLevel2::doShoot(float desplX, float desplY, float dirX, float dirY) {
	if (lastShoot == 0) {
		glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
		glm::vec2 dir = glm::vec2(dirX, dirY);
		sndPlaySound(TEXT("musica/level01-shoot.wav"), SND_ASYNC);
		BulletManager::instance().createPlayerBullet(pos, dir, 6, 1);
		lastShoot = Time::instance().getMili();
	}
	else {
		if (Time::instance().isAbleToShoot(lastShoot)) {
			glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			sndPlaySound(TEXT("musica/level01-shoot.wav"), SND_ASYNC);
			BulletManager::instance().createPlayerBullet(pos, dir, 6, 1);
			lastShoot = Time::instance().getMili();
		}
	}
}

void PlayerLevel2::setDeadState(bool dead) {
	if (dead && !isDead) {
		isDead = dead;
		--lifes;
	}
	else if (!dead && isDead) {
		isDead = dead;
		sprite->changeAnimation(STAND_NS);
		deadTime = 0;
	}
}

bool PlayerLevel2::getDeadState() {
	return isDead;
}

int PlayerLevel2::getDeadTime() {
	return deadTime;
}

int PlayerLevel2::getLifes() {
	return lifes;
}

void PlayerLevel2::setLifes(int l) {
	lifes = l;
}