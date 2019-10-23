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

	void init(TileMap* tileMap, ShaderProgram& shaderProgram, int level);
	void initLevel1(TileMap *tileMap, ShaderProgram& shaderProgram);
	void init2_1(TileMap* tileMap, ShaderProgram& shaderProgram);
	void init2_2(TileMap* tileMap, ShaderProgram& shaderProgram);
	void init2_3(TileMap* tileMap, ShaderProgram& shaderProgram);
	void init2_4(TileMap* tileMap, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	void render();

private:
	vector<Enemy*> enemies;


	bool isEnemyInside(glm::vec2 pos, glm::vec2 box);



};

