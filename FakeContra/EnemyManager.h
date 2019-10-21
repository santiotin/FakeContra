#include <String.h>
#include <vector>
#include "Turret1.h"
#include "TorRafaga1.h"
#include "Runner.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Enemy.h"
#include <glm/gtc/matrix_transform.hpp>


class EnemyManager
{

public:

	EnemyManager() {}

	// singleton
	static EnemyManager& instance()
	{
		static EnemyManager EM;

		return EM;
	}

	void init(TileMap *tileMap, ShaderProgram& shaderProgram, int level);
	void initLevel1(TileMap* tileMap, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	void render();

private:

	vector<Turret *> vecTurret;
	vector<TorRafaga *> vecTorRafaga;
	vector<Runner *> vecRunner;
	vector<Soldier *> vecSoldier;
	vector<Sniper *> vecSniper;

	vector<Enemy *> enemies;

};

