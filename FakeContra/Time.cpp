#include "Time.h"
#include <chrono>

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