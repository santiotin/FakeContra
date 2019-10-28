#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include <string>
#include <windows.h>


#define SUPERMODETIME 6000//6000

#define STANDBOX glm::vec2(40.f, 70.f)
#define BENDBOX glm::vec2(60.f, 25.f)
#define JUMPBOX glm::vec2(35.f, 35.f)
#define SWIMBOX glm::vec2(30.f, 35.f)

#define STANDSTARTP glm::vec2(0.f, 20.f)
#define BENDSTARTP glm::vec2(0.f, 60.f)
#define JUMPSTARTP glm::vec2(0.f, 60.f)
#define SWIMSTARTP glm::vec2(0.f, 55.f)

#include <Windows.h>
#include <mmsystem.h>

enum PlayerAnims
{
	STAND_FORW_LEFT_NS, STAND_FORW_LEFT_SH, STAND_FORW_RIGHT_NS, STAND_FORW_RIGHT_SH,

	STAND_UP_LEFT_NS, STAND_UP_LEFT_SH, STAND_UP_RIGHT_NS, STAND_UP_RIGHT_SH,

	DIAG_UP_LEFT_NS_SH, DIAG_UP_RIGHT_NS_SH,

	DIAG_DOWN_LEFT_NS_SH, DIAG_DOWN_RIGHT_NS_SH,

	MOVE_LEFT_NS, MOVE_LEFT_SH, MOVE_RIGHT_NS, MOVE_RIGHT_SH,

	JUMP_LEFT, JUMP_RIGHT,

	BEND_LEFT_NS, BEND_LEFT_SH, BEND_RIGHT_NS, BEND_RIGHT_SH,

	SWIM_FORW_LEFT_NS, SWIM_FORW_LEFT_SH, SWIM_FORW_RIGHT_NS, SWIM_FORW_RIGHT_SH,

	SWIM_UP_LEFT_NS, SWIM_UP_LEFT_SH, SWIM_UP_RIGHT_NS, SWIM_UP_RIGHT_SH,

	SWIM_DIAG_UP_LEFT_NS, SWIM_DIAG_UP_LEFT_SH, SWIM_DIAG_UP_RIGHT_NS, SWIM_DIAG_UP_RIGHT_SH,

	DIE_LEFT, DIE_RIGHT, DIE_SWIM,

	SWIM_BEND,
};

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	bSwim = false;
	lastShoot = 0;
	isDead = false;
	lifes = 3;
	deadTime = 0;
	hasSpreadGun = false;

	hasPowerUp = false;
	powerTime = 0;
	superMode = false;
	speedLinearBullet = 6.0f; //6
	speedDiagBullet = 3.5f; //3.5
	walkStep = 2; //2
	fallStep = 4; //4
	jumpHeight = 96; //96
	jumpAngleStep = 4; //4
	magicNumber = 8;

	boxPlayer = glm::vec2(30.0f, 30.0);

	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(38);
	
		//STAND FORW RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(STAND_FORW_LEFT_NS, 8);
		sprite->addKeyframe(STAND_FORW_LEFT_NS, glm::vec2(0.55f, 0.00f));
		sprite->setAnimationSpeed(STAND_FORW_LEFT_SH, 8);
		sprite->addKeyframe(STAND_FORW_LEFT_SH, glm::vec2(0.50f, 0.00f));
		sprite->setAnimationSpeed(STAND_FORW_RIGHT_NS, 8);
		sprite->addKeyframe(STAND_FORW_RIGHT_NS, glm::vec2(0.00f, 0.00f));
		sprite->setAnimationSpeed(STAND_FORW_RIGHT_SH, 8);
		sprite->addKeyframe(STAND_FORW_RIGHT_SH, glm::vec2(0.05f, 0.00f));

		//STAND UP RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(STAND_UP_LEFT_NS, 8);
		sprite->addKeyframe(STAND_UP_LEFT_NS, glm::vec2(0.45f, 0.00f));
		sprite->setAnimationSpeed(STAND_UP_LEFT_SH, 8);
		sprite->addKeyframe(STAND_UP_LEFT_SH, glm::vec2(0.40f, 0.00f));
		sprite->setAnimationSpeed(STAND_UP_RIGHT_NS, 8);
		sprite->addKeyframe(STAND_UP_RIGHT_NS, glm::vec2(0.10f, 0.00f));
		sprite->setAnimationSpeed(STAND_UP_RIGHT_SH, 8);
		sprite->addKeyframe(STAND_UP_RIGHT_SH, glm::vec2(0.15f, 0.00f));

		//DIAG UP RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(DIAG_UP_LEFT_NS_SH, 8);
		sprite->addKeyframe(DIAG_UP_LEFT_NS_SH, glm::vec2(0.55f, 0.25f));
		sprite->addKeyframe(DIAG_UP_LEFT_NS_SH, glm::vec2(0.50f, 0.25f));
		sprite->addKeyframe(DIAG_UP_LEFT_NS_SH, glm::vec2(0.45f, 0.25f));
		sprite->addKeyframe(DIAG_UP_LEFT_NS_SH, glm::vec2(0.40f, 0.25f));
		sprite->addKeyframe(DIAG_UP_LEFT_NS_SH, glm::vec2(0.35f, 0.25f));
		sprite->addKeyframe(DIAG_UP_LEFT_NS_SH, glm::vec2(0.30f, 0.25f));
		sprite->setAnimationSpeed(DIAG_UP_RIGHT_NS_SH, 8);
		sprite->addKeyframe(DIAG_UP_RIGHT_NS_SH, glm::vec2(0.00f, 0.25f));
		sprite->addKeyframe(DIAG_UP_RIGHT_NS_SH, glm::vec2(0.05f, 0.25f));
		sprite->addKeyframe(DIAG_UP_RIGHT_NS_SH, glm::vec2(0.10f, 0.25f));
		sprite->addKeyframe(DIAG_UP_RIGHT_NS_SH, glm::vec2(0.15f, 0.25f));
		sprite->addKeyframe(DIAG_UP_RIGHT_NS_SH, glm::vec2(0.20f, 0.25f));
		sprite->addKeyframe(DIAG_UP_RIGHT_NS_SH, glm::vec2(0.25f, 0.25f));

		//DIAG DOWN RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(DIAG_DOWN_LEFT_NS_SH, 8);
		sprite->addKeyframe(DIAG_DOWN_LEFT_NS_SH, glm::vec2(0.55f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_LEFT_NS_SH, glm::vec2(0.50f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_LEFT_NS_SH, glm::vec2(0.45f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_LEFT_NS_SH, glm::vec2(0.40f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_LEFT_NS_SH, glm::vec2(0.35f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_LEFT_NS_SH, glm::vec2(0.30f, 0.30f));
		sprite->setAnimationSpeed(DIAG_DOWN_RIGHT_NS_SH, 8);
		sprite->addKeyframe(DIAG_DOWN_RIGHT_NS_SH, glm::vec2(0.00f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_RIGHT_NS_SH, glm::vec2(0.05f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_RIGHT_NS_SH, glm::vec2(0.10f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_RIGHT_NS_SH, glm::vec2(0.15f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_RIGHT_NS_SH, glm::vec2(0.20f, 0.30f));
		sprite->addKeyframe(DIAG_DOWN_RIGHT_NS_SH, glm::vec2(0.25f, 0.30f));
		
		//MOVE LEFT RIGHT NO SHOOT SHOOT
		sprite->setAnimationSpeed(MOVE_LEFT_NS, 8);
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.55f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.50f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.45f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.40f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.35f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.30f, 0.05f));
		sprite->setAnimationSpeed(MOVE_LEFT_SH, 8);
		sprite->addKeyframe(MOVE_LEFT_SH, glm::vec2(0.55f, 0.15f));
		sprite->addKeyframe(MOVE_LEFT_SH, glm::vec2(0.50f, 0.15f));
		sprite->addKeyframe(MOVE_LEFT_SH, glm::vec2(0.45f, 0.15f));
		sprite->addKeyframe(MOVE_LEFT_SH, glm::vec2(0.40f, 0.15f));
		sprite->addKeyframe(MOVE_LEFT_SH, glm::vec2(0.35f, 0.15f));
		sprite->addKeyframe(MOVE_LEFT_SH, glm::vec2(0.30f, 0.15f));
		sprite->setAnimationSpeed(MOVE_RIGHT_NS, 8);
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.00f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.05f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.10f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.15f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.20f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.25f, 0.05f));
		sprite->setAnimationSpeed(MOVE_RIGHT_SH, 8);
		sprite->addKeyframe(MOVE_RIGHT_SH, glm::vec2(0.00f, 0.15f));
		sprite->addKeyframe(MOVE_RIGHT_SH, glm::vec2(0.05f, 0.15f));
		sprite->addKeyframe(MOVE_RIGHT_SH, glm::vec2(0.10f, 0.15f));
		sprite->addKeyframe(MOVE_RIGHT_SH, glm::vec2(0.15f, 0.15f));
		sprite->addKeyframe(MOVE_RIGHT_SH, glm::vec2(0.20f, 0.15f));
		sprite->addKeyframe(MOVE_RIGHT_SH, glm::vec2(0.25f, 0.15f));

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

		//BEND LEFT RIGHT
		sprite->setAnimationSpeed(BEND_LEFT_NS, 8);
		sprite->addKeyframe(BEND_LEFT_NS, glm::vec2(0.35f, 0.00f));
		sprite->setAnimationSpeed(BEND_LEFT_SH, 8);
		sprite->addKeyframe(BEND_LEFT_SH, glm::vec2(0.30f, 0.00f));
		sprite->setAnimationSpeed(BEND_RIGHT_NS, 8);
		sprite->addKeyframe(BEND_RIGHT_NS, glm::vec2(0.20f, 0.00f));
		sprite->setAnimationSpeed(BEND_RIGHT_SH, 8);
		sprite->addKeyframe(BEND_RIGHT_SH, glm::vec2(0.25f, 0.00f));

		//SWIM FORW RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(SWIM_FORW_LEFT_NS, 8);
		sprite->addKeyframe(SWIM_FORW_LEFT_NS, glm::vec2(0.35f, 0.40f));
		sprite->setAnimationSpeed(SWIM_FORW_LEFT_SH, 8);
		sprite->addKeyframe(SWIM_FORW_LEFT_SH, glm::vec2(0.50f, 0.35f));
		sprite->setAnimationSpeed(SWIM_FORW_RIGHT_NS, 8);
		sprite->addKeyframe(SWIM_FORW_RIGHT_NS, glm::vec2(0.20f, 0.40f));
		sprite->setAnimationSpeed(SWIM_FORW_RIGHT_SH, 8);
		sprite->addKeyframe(SWIM_FORW_RIGHT_SH, glm::vec2(0.05f, 0.35f));

		//SWIM UP RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(SWIM_UP_LEFT_NS, 8);
		sprite->addKeyframe(SWIM_UP_LEFT_NS, glm::vec2(0.30f, 0.35f));
		sprite->setAnimationSpeed(SWIM_UP_LEFT_SH, 8);
		sprite->addKeyframe(SWIM_UP_LEFT_SH, glm::vec2(0.35f, 0.35f));
		sprite->setAnimationSpeed(SWIM_UP_RIGHT_NS, 8);
		sprite->addKeyframe(SWIM_UP_RIGHT_NS, glm::vec2(0.25f, 0.35f));
		sprite->setAnimationSpeed(SWIM_UP_RIGHT_SH, 8);
		sprite->addKeyframe(SWIM_UP_RIGHT_SH, glm::vec2(0.20f, 0.35f));

		//SWIM DIAG RIGHT LEFT SHOOT NO SHOT
		sprite->setAnimationSpeed(SWIM_DIAG_UP_LEFT_NS, 8);
		sprite->addKeyframe(SWIM_DIAG_UP_LEFT_NS, glm::vec2(0.40f, 0.35f));
		sprite->setAnimationSpeed(SWIM_DIAG_UP_LEFT_SH, 8);
		sprite->addKeyframe(SWIM_DIAG_UP_LEFT_SH, glm::vec2(0.45f, 0.35f));
		sprite->setAnimationSpeed(SWIM_DIAG_UP_RIGHT_NS, 8);
		sprite->addKeyframe(SWIM_DIAG_UP_RIGHT_NS, glm::vec2(0.15f, 0.35f));
		sprite->setAnimationSpeed(SWIM_DIAG_UP_RIGHT_SH, 8);
		sprite->addKeyframe(SWIM_DIAG_UP_RIGHT_SH, glm::vec2(0.10f, 0.35f));

		//SWIM_BEND
		sprite->setAnimationSpeed(SWIM_BEND, 8);
		sprite->addKeyframe(SWIM_BEND, glm::vec2(0.05f, 0.40f));

		//DIE
		sprite->setAnimationSpeed(DIE_LEFT, 8);
		sprite->addKeyframe(DIE_LEFT, glm::vec2(0.35f, 0.20f));
		sprite->setAnimationSpeed(DIE_RIGHT, 8);
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(0.20f, 0.20f));
		sprite->setAnimationSpeed(DIE_SWIM, 8);
		sprite->addKeyframe(DIE_SWIM, glm::vec2(0.00f, 0.40f));

		
	sprite->changeAnimation(2);
	bDir = true;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	bSwim = map->inWaterToSwim(posPlayer, glm::ivec2(32, 32));

	changeToNormalMode();
	if (Game::instance().getKey(32)) changeToSuperMode();

	if (!isDead) {

		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			bDir = false;

			if (!bJumping && !bSwim) {
				setBox(STANDBOX);
				if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
					if (sprite->animation() != DIAG_UP_LEFT_NS_SH) sprite->changeAnimation(DIAG_UP_LEFT_NS_SH);
					else if (Game::instance().getKey('x')) doShoot(-10.f, -65.f, -1.5f, -1.f, speedDiagBullet);
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
					if (sprite->animation() != DIAG_DOWN_LEFT_NS_SH) sprite->changeAnimation(DIAG_DOWN_LEFT_NS_SH);
					else if (Game::instance().getKey(int('x'))) doShoot(-15.f, -15.f, -1.5f, 1.f, speedDiagBullet);
				}
				else {
					if (Game::instance().getKey(int('x')) && sprite->animation() != MOVE_LEFT_SH) sprite->changeAnimation(MOVE_LEFT_SH);
					else if (Game::instance().getKey(int('x')) && sprite->animation() == MOVE_LEFT_SH) doShoot(-5.f, -40.f, -1.f, 0.0f, speedLinearBullet);
					else if (!Game::instance().getKey(int('x')) && sprite->animation() != MOVE_LEFT_NS) sprite->changeAnimation(MOVE_LEFT_NS);

				}
			}
			else if (bSwim) {
				setBox(SWIMBOX);
				if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
					if (Game::instance().getKey(int('x')) && sprite->animation() != SWIM_DIAG_UP_LEFT_SH) sprite->changeAnimation(SWIM_DIAG_UP_LEFT_SH);
					else if (Game::instance().getKey(int('x')) && sprite->animation() == SWIM_DIAG_UP_LEFT_SH) doShoot(-10.f, -30.f, -1.5f, -1.f, speedDiagBullet);
					else if (!Game::instance().getKey(int('x')) && sprite->animation() != SWIM_DIAG_UP_LEFT_NS) sprite->changeAnimation(SWIM_DIAG_UP_LEFT_NS);

				}
				else {
					if (Game::instance().getKey(int('x')) && sprite->animation() != SWIM_FORW_LEFT_SH) sprite->changeAnimation(SWIM_FORW_LEFT_SH);
					else if (Game::instance().getKey(int('x')) && sprite->animation() == SWIM_FORW_LEFT_SH) doShoot(-5.f, -8.f, -1.f, 0.0f, speedLinearBullet);
					else if (!Game::instance().getKey(int('x')) && sprite->animation() != SWIM_FORW_LEFT_NS) sprite->changeAnimation(SWIM_FORW_LEFT_NS);

				}
			}

			posPlayer.x -= walkStep;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += walkStep;
				if (!bJumping) sprite->changeAnimation(STAND_FORW_LEFT_NS);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			bDir = true;
			if (!bJumping && !bSwim) {
				setBox(STANDBOX);
				if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
					if (sprite->animation() != DIAG_UP_RIGHT_NS_SH)sprite->changeAnimation(DIAG_UP_RIGHT_NS_SH);
					else if (Game::instance().getKey(int('x'))) doShoot(45.f, -70.f, 1.5f, -1.f, speedDiagBullet);
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
					if (sprite->animation() != DIAG_DOWN_RIGHT_NS_SH) sprite->changeAnimation(DIAG_DOWN_RIGHT_NS_SH);
					else if (Game::instance().getKey(int('x'))) doShoot(62.f, -10.f, 1.5f, 1.f, speedDiagBullet);
				}
				else {
					if (Game::instance().getKey(int('x')) && sprite->animation() != MOVE_RIGHT_SH) sprite->changeAnimation(MOVE_RIGHT_SH);
					else if (Game::instance().getKey(int('x')) && sprite->animation() == MOVE_RIGHT_SH) doShoot(45.f, -40.f, 1.f, 0.0f, speedLinearBullet);
					else if (!Game::instance().getKey(int('x')) && sprite->animation() != MOVE_RIGHT_NS) sprite->changeAnimation(MOVE_RIGHT_NS);


				}
			}
			else if (bSwim) {
				setBox(SWIMBOX);
				if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
					if (Game::instance().getKey(int('x')) && sprite->animation() != SWIM_DIAG_UP_RIGHT_SH) sprite->changeAnimation(SWIM_DIAG_UP_RIGHT_SH);
					else if (Game::instance().getKey(int('x')) && sprite->animation() == SWIM_DIAG_UP_RIGHT_SH) doShoot(40.f, -30.f, 1.5f, -1.f, speedDiagBullet);
					else if (!Game::instance().getKey(int('x')) && sprite->animation() != SWIM_DIAG_UP_RIGHT_NS) sprite->changeAnimation(SWIM_DIAG_UP_RIGHT_NS);


				}
				else {
					if (Game::instance().getKey(int('x')) && sprite->animation() != SWIM_FORW_RIGHT_SH) sprite->changeAnimation(SWIM_FORW_RIGHT_SH);
					else if (Game::instance().getKey(int('x')) && sprite->animation() == SWIM_FORW_RIGHT_SH) doShoot(40.f, -8.f, 1.f, 0.0f, speedLinearBullet);
					else if (!Game::instance().getKey(int('x')) && sprite->animation() != SWIM_FORW_RIGHT_NS) sprite->changeAnimation(SWIM_FORW_RIGHT_NS);

				}
			}

			posPlayer.x += walkStep;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= walkStep;
				if (!bJumping) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (!bJumping && !bSwim) {
				setBox(BENDBOX);
				if (bDir) {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(BEND_RIGHT_SH);
						doShoot(60.f, -13.f, 1.f, 0.f, speedLinearBullet);
					}
					else sprite->changeAnimation(BEND_RIGHT_NS);
				}
				else {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(BEND_LEFT_SH);
						doShoot(0.f, -13.f, -1.f, 0.f, speedLinearBullet);
					}
					else sprite->changeAnimation(BEND_LEFT_NS);
				}
			}
			else if (bSwim) {
				setBox(SWIMBOX);
				sprite->changeAnimation(SWIM_BEND);
			}


		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			if (!bJumping && !bSwim) {
				setBox(STANDBOX);
				if (bDir) {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(STAND_UP_RIGHT_SH);
						doShoot(20.f, -80.f, 0.f, -1.f, speedLinearBullet);
					}
					else sprite->changeAnimation(STAND_UP_RIGHT_NS);
				}
				else {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(STAND_UP_LEFT_SH);
						doShoot(5.f, -80.f, 0.f, -1.f, speedLinearBullet);
					}
					else sprite->changeAnimation(STAND_UP_LEFT_NS);
				}
			}
			else if (bSwim) {
				setBox(SWIMBOX);
				if (bDir) {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(SWIM_UP_RIGHT_SH);
						doShoot(25.f, -50.f, 0.f, -1.f, speedLinearBullet);
					}
					else sprite->changeAnimation(SWIM_UP_RIGHT_NS);
				}
				else {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(SWIM_UP_LEFT_SH);
						doShoot(5.f, -50.f, 0.f, -1.f, speedLinearBullet);
					}
					else sprite->changeAnimation(SWIM_UP_LEFT_NS);
				}
			}

		}

		else
		{
			if (!bJumping && !bSwim) {
				setBox(STANDBOX);
				if (bDir) {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(STAND_FORW_RIGHT_SH);
						doShoot(41.f, -40.f, 1.f, 0.0f, speedLinearBullet);
					}
					else sprite->changeAnimation(STAND_FORW_RIGHT_NS);
				}
				else {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(STAND_FORW_LEFT_SH);
						doShoot(0.f, -40.f, -1.f, 0.0f, speedLinearBullet);
					}
					else sprite->changeAnimation(STAND_FORW_LEFT_NS);

				}
			}
			else if (bSwim) {
				setBox(SWIMBOX);
				if (bDir) {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(SWIM_FORW_RIGHT_SH);
						doShoot(40.f, -8.f, 1.f, 0.0f, speedLinearBullet);
					}
					else sprite->changeAnimation(SWIM_FORW_RIGHT_NS);
				}
				else {
					if (Game::instance().getKey(int('x'))) {
						sprite->changeAnimation(SWIM_FORW_LEFT_SH);
						doShoot(0.f, -8.f, -1.f, 0.0f, speedLinearBullet);
					}
					else sprite->changeAnimation(SWIM_FORW_LEFT_NS);

				}
			}
		}

		if (bJumping) {
			setBox(JUMPBOX);
			if (bDir && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
			else if (!bDir && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);

			jumpAngle += jumpAngleStep;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
				if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_FORW_LEFT_NS);
				else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
			}
			else
			{
				posPlayer.y = int(startY - jumpHeight * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, magicNumber);
			}
		}
		else if (!bSwim)
		{
			posPlayer.y += fallStep;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, magicNumber))
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
		deadTime++;
		if (!bSwim) {
			if (bDir && sprite->animation() != DIE_RIGHT) sprite->changeAnimation(DIE_RIGHT);
			else if (!bDir && sprite->animation() != DIE_LEFT) sprite->changeAnimation(DIE_LEFT);

			posPlayer.y += fallStep;
			map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, magicNumber);
		}
		else {
			if (sprite->animation() != DIE_SWIM) sprite->changeAnimation(DIE_SWIM);
		}
		
	}
	
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}

float Player::getPosX() 
{
	//prova de canvi de branca
	return float(posPlayer.x);
}

float Player::getPosY()
{
	return float(posPlayer.y);
}

glm::vec2 Player::getBox()
{
	return boxPlayer;
}

glm::vec2 Player::getStartP() {
	if (getBox().x == STANDBOX.x && getBox().y == STANDBOX.y) return STANDSTARTP;
	else if (getBox().x == BENDBOX.x && getBox().y == BENDBOX.y) return BENDSTARTP;
	else if (getBox().x == JUMPBOX.x && getBox().y == JUMPBOX.y) return JUMPSTARTP;
	else if (getBox().x == SWIMBOX.x && getBox().y == SWIMBOX.y) return SWIMSTARTP;

	return STANDSTARTP;
}

void Player::setStartP(glm::vec2 start) {
	startP = start;
}

void Player::setBox(glm::vec2 box)
{
	boxPlayer = box;
}

void Player::doShoot(float desplX, float desplY, float dirX, float dirY, float speed) {
	if (lastShoot == 0) {
		lastShoot = Time::instance().getMili();
		if (hasSpreadGun) {
			doShootSpreadGun(desplX, desplY, dirX, dirY, speed);
		}
		else {

			glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
			glm::vec2 dir = glm::vec2(dirX, dirY);
			sndPlaySound(TEXT("musica/level01-shoot.wav"), SND_ASYNC);
			BulletManager::instance().createPlayerBullet(pos, dir, speed, 0);
		}
	}
	else {
		if (hasSpreadGun) {
			if (Time::instance().isAbleToShootSpread(lastShoot)) {
				lastShoot = Time::instance().getMili();
				doShootSpreadGun(desplX, desplY, dirX, dirY, speed);
			}
		}
		else {
			if (Time::instance().isAbleToShoot(lastShoot)) {
				lastShoot = Time::instance().getMili();
				glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
				glm::vec2 dir = glm::vec2(dirX, dirY);
				sndPlaySound(TEXT("musica/level01-shoot.wav"), SND_ASYNC);
				BulletManager::instance().createPlayerBullet(pos, dir, speed, 0);
			}
		}
	}
}

void Player::doShootSpreadGun(float desplX, float desplY, float dirX, float dirY, float speed) {
	glm::vec2 pos = glm::vec2(posPlayer.x + desplX, posPlayer.y + desplY);
	glm::vec2 dir1;
	glm::vec2 dir2;
	glm::vec2 dir3;
	if (dirX == 0) {
		dir1 = glm::vec2(dirX, dirY);
		dir2 = glm::vec2(dirX + 1.0, dirY);
		dir3 = glm::vec2(dirX - 1.0, dirY);
	}
	else if (dirY == 0) {
		dir1 = glm::vec2(dirX, dirY);
		dir2 = glm::vec2(dirX, dirY + 1.0 );
		dir3 = glm::vec2(dirX, dirY - 1.0);
	}
	else {
		dir1 = glm::vec2(dirX, dirY);
		dir2 = glm::vec2(dirX * 2.0, dirY);
		dir3 = glm::vec2(dirX, dirY * 2.0);
	}
	sndPlaySound(TEXT("musica/level01-shoot.wav"), SND_ASYNC);
	BulletManager::instance().createPlayerBullet(pos, dir1, speed + 1.0, 0);
	BulletManager::instance().createPlayerBullet(pos, dir2, speed - 0.5, 0);
	BulletManager::instance().createPlayerBullet(pos, dir3, speed - 0.5, 0);
}

void Player::setDeadState(bool dead) {
	if (dead && !isDead) {
		isDead = dead;
		--lifes;
	}
	else if (!dead && isDead) {
		isDead = dead;
		sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		deadTime = 0;
	}
}

bool Player::getDeadState() {
	return isDead;
}

int Player::getDeadTime() {
	return deadTime;
}

int Player::getLifes() {
	return lifes;
}

void Player::changeToSuperMode() {
	if (hasPowerUp) {
		powerTime = Time::instance().getMili();
		hasPowerUp = false;

		superMode = true;
		speedLinearBullet = 6.0f; //6
		speedDiagBullet = 7.0f; //3.5
		walkStep = 4; //2
		fallStep = 8; //4
		jumpHeight = 192; //96
		jumpAngleStep = 4; //4
		magicNumber = 16;
	}
}

void Player::changeToNormalMode() {
	if (Time::instance().getMili() - powerTime > SUPERMODETIME) {
		
		superMode = false;
		speedLinearBullet = 6.0f; //6
		speedDiagBullet = 3.5f; //3.5
		walkStep = 2; //2
		fallStep = 4; //4
		jumpHeight = 96; //96
		jumpAngleStep = 4; //4
		magicNumber = 8;
	}
}

bool Player::getMode() {
	return superMode;
}

bool Player::getHasPower() {
	return hasPowerUp;
}

void Player::setHasPower() {
	hasPowerUp = true;
}

bool Player::getHasSpreadGun() {
	return hasSpreadGun;
}

void Player::setHasSpreadGun() {
	hasSpreadGun = true;
}





