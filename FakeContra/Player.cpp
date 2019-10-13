#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define WALK_STEP 2;


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

	DIE_LEFT, DIE_RIGHT,

	SWIM_BEND,
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(37);
	
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

		
	sprite->changeAnimation(2);
	bDir = true;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP) && !bJumping) {
		bDir = false;
		if (sprite->animation() != DIAG_UP_LEFT_NS_SH) sprite->changeAnimation(DIAG_UP_LEFT_NS_SH);
		
		posPlayer.x -= WALK_STEP;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_LEFT_NS);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP) && !bJumping) {
		bDir = true;
		if (sprite->animation() != DIAG_UP_RIGHT_NS_SH) sprite->changeAnimation(DIAG_UP_RIGHT_NS_SH);

		posPlayer.x += WALK_STEP;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !bJumping) {
		bDir = false;
		if (sprite->animation() != DIAG_DOWN_LEFT_NS_SH) sprite->changeAnimation(DIAG_DOWN_LEFT_NS_SH);

		posPlayer.x -= WALK_STEP;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_LEFT_NS);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !bJumping) {
		bDir = true;
		if (sprite->animation() != DIAG_DOWN_RIGHT_NS_SH) sprite->changeAnimation(DIAG_DOWN_RIGHT_NS_SH);

		posPlayer.x += WALK_STEP;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		bDir = false;
		if (!bJumping) {
			if (Game::instance().getKey(int('x')) && sprite->animation() != MOVE_LEFT_SH) sprite->changeAnimation(MOVE_LEFT_SH);
			else if (!Game::instance().getKey(int('x')) && sprite->animation() != MOVE_LEFT_NS) sprite->changeAnimation(MOVE_LEFT_NS);
		}
		
		posPlayer.x -= WALK_STEP;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_LEFT_NS);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		bDir = true;
		if (!bJumping) {
			if (Game::instance().getKey(int('x')) && sprite->animation() != MOVE_RIGHT_SH) sprite->changeAnimation(MOVE_RIGHT_SH);
			else if (!Game::instance().getKey(int('x')) && sprite->animation() != MOVE_RIGHT_NS) sprite->changeAnimation(MOVE_RIGHT_NS);
		}
		
		posPlayer.x += WALK_STEP;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !bJumping) {
		if (bDir) {
			if (Game::instance().getKey(int('x'))) sprite->changeAnimation(BEND_RIGHT_SH);
			else sprite->changeAnimation(BEND_RIGHT_NS);
		}
		else {
			if (Game::instance().getKey(int('x'))) sprite->changeAnimation(BEND_LEFT_SH);
			else sprite->changeAnimation(BEND_LEFT_NS);
		}

	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !bJumping) {
		if (bDir) {
			if (Game::instance().getKey(int('x'))) sprite->changeAnimation(STAND_UP_RIGHT_SH);
			else sprite->changeAnimation(STAND_UP_RIGHT_NS);
		}
		else {
			if (Game::instance().getKey(int('x'))) sprite->changeAnimation(STAND_UP_LEFT_SH);
			else sprite->changeAnimation(STAND_UP_LEFT_NS);
		}
	}
	
	else
	{
		if (!bJumping) {
			if (bDir) {
				if (Game::instance().getKey(int('x'))) sprite->changeAnimation(STAND_FORW_RIGHT_SH);
				else sprite->changeAnimation(STAND_FORW_RIGHT_NS);
			}
			else {
				if (Game::instance().getKey(int('x'))) sprite->changeAnimation(STAND_FORW_LEFT_SH);
				else sprite->changeAnimation(STAND_FORW_LEFT_NS);
				
			}
		}
	}
	
	if(bJumping)
	{
		if (bDir && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
		else if (!bDir && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);

		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_FORW_LEFT_NS);
			else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			//if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			if(Game::instance().getKey(int('z')))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
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

float Player::getPosX() 
{
	return float(posPlayer.x);
}




