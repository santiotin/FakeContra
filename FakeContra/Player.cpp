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
	STAND_FORW_LEFT_NS, STAND_FOR_LEFT_SH, STAND_FORW_RIGHT_NS, STAND_FORW_RIGHT_SH,
	STAND_UP_LEFT_NS, STAND_UP_LEFT_SH, STAND_UP_RIGHT_NS, STAND_UP_RIGHT_SH,
	STAND_DOWN_LEFT_NS, STAND_DOWN_LEFT_SH, STAND_DOWN_RIGHT_NS, STAND_DOWN_RIGHT_SH,
	MOVE_LEFT_NS, MOVE_LEFT_SH, MOVE_RIGHT_NS, MOVE_RIGHT_SH,
	JUMP_LEFT, JUMP_RIGHT,
	SWIM_FORW_LEFT_NS, SWIM_FOR_LEFT_SH, SWIM_FORW_RIGHT_NS, SWIM_FORW_RIGHT_SH,
	SWIM_UP_LEFT_NS, SWIM_UP_LEFT_SH, SWIM_UP_RIGHT_NS, SWIM_UP_RIGHT_SH,
	BEND_LEFT, BEND_RIGHT,
	DIEW_LEFT, DIE_RIGHT,
	CHOF,
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/personaje.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(0.05, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	
		sprite->setAnimationSpeed(STAND_FORW_LEFT_NS, 8);
		sprite->addKeyframe(STAND_FORW_LEFT_NS, glm::vec2(0.55f, 0.00f));
		
		sprite->setAnimationSpeed(STAND_FORW_RIGHT_NS, 8);
		sprite->addKeyframe(STAND_FORW_RIGHT_NS, glm::vec2(0.0f, 0.00f));
		
		sprite->setAnimationSpeed(MOVE_LEFT_NS, 8);
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.55f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.50f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.45f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.40f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.35f, 0.05f));
		sprite->addKeyframe(MOVE_LEFT_NS, glm::vec2(0.30f, 0.05f));

		sprite->setAnimationSpeed(MOVE_RIGHT_NS, 8);
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.00f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.05f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.10f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.15f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.20f, 0.05f));
		sprite->addKeyframe(MOVE_RIGHT_NS, glm::vec2(0.25f, 0.05f));

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

		sprite->setAnimationSpeed(BEND_LEFT, 8);
		sprite->addKeyframe(BEND_LEFT, glm::vec2(0.30f, 0.00f));

		sprite->setAnimationSpeed(BEND_RIGHT, 8);
		sprite->addKeyframe(BEND_RIGHT, glm::vec2(0.20f, 0.00f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!bJumping && sprite->animation() != MOVE_LEFT_NS) sprite->changeAnimation(MOVE_LEFT_NS);
		else if (bJumping && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);
		posPlayer.x -= WALK_STEP;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += WALK_STEP;
			if(!bJumping) sprite->changeAnimation(STAND_FORW_LEFT_NS);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(!bJumping && sprite->animation() != MOVE_RIGHT_NS) sprite->changeAnimation(MOVE_RIGHT_NS);
		if(bJumping && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
		posPlayer.x += WALK_STEP;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= WALK_STEP;
			if (!bJumping) sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !bJumping)
	{
		if (sprite->animation() == MOVE_RIGHT_NS || sprite->animation() == STAND_FORW_RIGHT_NS) sprite->changeAnimation(BEND_RIGHT);
		if (sprite->animation() == MOVE_LEFT_NS || sprite->animation() == STAND_FORW_LEFT_NS) sprite->changeAnimation(BEND_LEFT);
	}
	
	else
	{
		if (!bJumping) {
			if (sprite->animation() == MOVE_LEFT_NS || sprite->animation() == BEND_LEFT)
				sprite->changeAnimation(STAND_FORW_LEFT_NS);
			else if (sprite->animation() == MOVE_RIGHT_NS || sprite->animation() == BEND_RIGHT)
				sprite->changeAnimation(STAND_FORW_RIGHT_NS);
		}
	}
	
	if(bJumping)
	{
		if (sprite->animation() == MOVE_LEFT_NS || sprite->animation() == STAND_FORW_LEFT_NS) sprite->changeAnimation(JUMP_LEFT);
		else if (sprite->animation() == MOVE_RIGHT_NS || sprite->animation() == STAND_FORW_RIGHT_NS) sprite->changeAnimation(JUMP_RIGHT);

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
		if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_FORW_LEFT_NS);
		else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_FORW_RIGHT_NS);

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




