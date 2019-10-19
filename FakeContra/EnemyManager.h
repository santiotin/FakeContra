#include <String.h>
#include <vector>
#include "Turret1.h"
#include "TorRafaga1.h"
#include "Runner.h"
#include "Soldier.h"
#include "Sniper.h"
#include <glm/gtc/matrix_transform.hpp>
class EnemyManager
{
public:
	void init(TileMap *tileMap, ShaderProgram& shaderProgram);
	void update(int deltaTime, float posPlayerX, float posPlayerY);
	void render();
private:

	vector<Turret *> vecTurret;
	vector<TorRafaga *> vecTorRafaga;
	vector<Runner *> vecRunner;
	vector<Soldier *> vecSoldier;
	vector<Sniper *> vecSniper;
};

