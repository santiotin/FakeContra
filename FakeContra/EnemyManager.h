#include <String.h>
#include <vector>
#include "Turret1.h"
#include "TorRafaga1.h"
#include "Runner.h"
#include "Soldier.h"
#include "Sniper.h"

#include "GreenSoldier.h"
#include "TorS2.h"
#include "BolS2.h"
#include "BigS2.h"
#include "Time.h"
#include "Enemy.h"
#include "TorBoss.h"
#include "TorBlue.h"
#include "BigS2.h"
#include "RafBoss.h"
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

	void init(TileMap* tileMap, ShaderProgram& shaderProgram, int level);

	void initLevel1(TileMap *tileMap, ShaderProgram& shaderProgram);

	void initLevel2_1( ShaderProgram& shaderProgram);
	void initLevel2_2(ShaderProgram& shaderProgram);
	void initLevel2_3( ShaderProgram& shaderProgram);
	void initLevel2_4( ShaderProgram& shaderProgram);
	void initLevel_Boss(ShaderProgram& shaderProgram);

	void update(int deltaTime, float posPlayerX, float posPlayerY, bool isDead);
	void render();
	void greenSoldier(ShaderProgram& shaderProgram);
	
	
	int getKills();
	int getSize();
	bool isEmpty();
	void isFaseBoss(bool fb);
	void transition(bool trans);
	void cleanEnemies();
	bool isBoss();
	bool isTrans();
	bool isEnemyInside(glm::vec2 pos, glm::vec2 box);

private:
	int kills, lvl;
	bool changing;
	bool boss;
	long long segs;
	vector<Enemy*> enemies;
	ShaderProgram sh;
};

