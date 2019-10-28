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
void Music::stop_song() {
		SoundEngine->stopAllSounds();
}

void Music::player_shoot()
{
	SoundEngine->play2D("musica/level01-shoot.wav", GL_TRUE);
}
void Music::game_over()
{
	SoundEngine->play2D("musica/game_over.wav", GL_TRUE);
}
void Music::win()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("musica/gg.wav", GL_TRUE);
}
void Music::gover(bool lose) {
	go = lose;
}
bool Music::isGo() {
	return go;
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