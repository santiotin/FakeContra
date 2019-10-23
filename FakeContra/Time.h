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
	bool isAbleToShootSoldier(long long lastShoot);
	bool isAbleToShootEnemy(long long lastShoot);
};

