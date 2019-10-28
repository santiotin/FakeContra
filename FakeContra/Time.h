#include <string>
using namespace std;





#pragma once
class Time
{

public:
	Time() {}

	// singleton
	static Time& instance()
	{
		static Time T;

		return T;
	}
	string getMiliString() const;
	long long getMili() const;
	bool isAbleToShoot(long long lastShoot);
	bool isAbleToShootSpread(long long lastShoot);
	bool isAbleToShootSoldier(long long lastShoot);
	bool isAbleToShootEnemy(long long lastShoot);
	bool isAbleToShootEnemyLevel2(long long lastShoot);
	bool isAbleToShootEnemyLevel3(long long lastShoot, int randm, int time);
	bool createGS(long long lastCreate);
};

