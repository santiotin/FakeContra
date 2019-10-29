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
	void stop_song();
	void soldier_shoot();
	void turret_shoot();
	void player_shoot();
	void game_over();
	void gover(bool lose);
	bool isGo();
	void win();

	bool menu, lvl1, go;
};

