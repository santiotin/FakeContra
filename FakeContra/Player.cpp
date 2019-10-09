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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, FALL_LEFT, FALL_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 32), glm::vec2(0.1666, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.1666f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.3333f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5000f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6666f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8333f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5000f, 0.25f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5000f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.6666f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8333f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5000f, 0.0f));

		sprite->setAnimationSpeed(JUMP_LEFT, 8);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.0000f, 0.75f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.1666f, 0.75f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.3333f, 0.75f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5000f, 0.75f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 8);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.0000f, 0.5f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.1666f, 0.5f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.3333f, 0.5f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5000f, 0.5f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (bJumping) {

			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
				sprite->changeAnimation(JUMP_LEFT);
		}
		else {
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
		}
		posPlayer.x -= WALK_STEP;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += WALK_STEP;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += WALK_STEP;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= WALK_STEP;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
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




