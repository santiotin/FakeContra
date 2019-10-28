#include "Music.h"
#include <stdlib.h>


using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();

void Music::song(int song)
{
	if (song == 0) {
		SoundEngine->stopAllSounds();
		SoundEngine->play2D("musica/menu-music.wav", GL_TRUE);
	}
	
	else if (song > 0) {
		SoundEngine->stopAllSounds();
		SoundEngine->play2D("musica/lvl01.wav", GL_TRUE);
	}
}

void Music::lvl1_song()
{
	SoundEngine->play2D("musica/lvl01.wav", GL_TRUE);
}

void Music::player_shoot()
{
	SoundEngine->play2D("musica/level01-shoot.wav", GL_TRUE);
}

void Music::soldier_shoot()
{
	SoundEngine->play2D("musica/level01-sniper-shoot.wav", GL_TRUE);
}

void Music::turret_shoot()
{
	SoundEngine->play2D("musica/level01-turret-shoot.wav", GL_TRUE);
}
//commit