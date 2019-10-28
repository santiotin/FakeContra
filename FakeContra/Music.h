#pragma once
#include <string>
#include <irrKlang.h>
#include <GL/glew.h>
#include <GL/glut.h>
using namespace std;
class Music
{

public:
	Music() {}

	// singleton
	static Music& instance()
	{
		static Music M;

		return M;
	}
	
	void song(int lvl);
	void lvl1_song();
	void soldier_shoot();
	void turret_shoot();
	void player_shoot();

	bool menu, lvl1;
};

