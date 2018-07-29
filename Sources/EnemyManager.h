#pragma once
#include "Simple2D.h"
#include "Spaceship.h"
#include "Meteor.h"
#include "Helper.h"
#include <vector>
#include <list>
using namespace std;


// responsible for enemy ships' and meteors' spawn and movement path during their lifetime
class EnemyManager {

private:
	
	float spawnRandomTimer = 0, spawnMeteorRandomTimer = 0;
	// meteor groups
	// 0: appear single, rotate 
	// 1: 2*2 form a bigger
	// 2: form meteor rain
	// 3: appear single, 2 life

	float spawnX, spawnYMax;

public:
	EnemyManager();
	~EnemyManager();
	list<EnemyShip*> enemyShips;
	list<Meteor*> meteors;
	// stage 1: random spawn, no special movement
	// stage 2: 
	void spawnRandom(float enemyCD);
	void spawnMeteorRandom(float cd);
	void update();

};