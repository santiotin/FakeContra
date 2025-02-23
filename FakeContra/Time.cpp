#include "Time.h"
#include <chrono>
#include <stdlib.h>


string Time::getMiliString() const
{
	chrono::system_clock::time_point p = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(p);
	char str[26];
	ctime_s(str, sizeof str, &t);
	return str;

}

long long Time::getMili() const
{
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	return std::stoll(std::to_string(millis), 0, 0);
}

bool Time::isAbleToShoot(long long lastShoot) {

	if (getMili() - lastShoot < 250) return false;
	else return true;
}

bool Time::isAbleToShootSpread(long long lastShoot) {

	if (getMili() - lastShoot < 750) return false;
	else return true;
}

bool Time::isAbleToShootSoldier(long long lastShoot) {

	if (getMili() - lastShoot < 250) return false;
	else return true;
}

bool Time::isAbleToShootEnemy(long long lastShoot) {

	if (getMili() - lastShoot < 1500) return false;
	else return true;
}
bool Time::createGS(long long lastCreate) {

	if (getMili() - lastCreate < 2000) return false;
	else return true;
}

bool Time::isAbleToShootEnemyLevel2(long long lastShoot) {
	
	if (getMili() - lastShoot < 3000) return false;
	else {
		int num = rand() % 19;
		if (num == 3) return true;
		else return false;
	}
}

bool Time::isAbleToShootEnemyLevel3(long long lastShoot, int randm,int time) {

	if (getMili() - lastShoot < 2000) return false;
	else {
		int num = rand() % randm;
		if (num == 3) return true;
		else return false;
	}
}

//commit