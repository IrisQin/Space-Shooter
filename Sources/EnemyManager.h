#pragma once
#include "Simple2D.h"
#include "Spaceship.h"
#include "Factory.cpp"
#include "Helper.h"
#include <vector>
#include <list>
using namespace std;

class EnemyManager {
private:
	
	float spawnRandomTimer = 0;
	float spawnX = 0;
	float spawnYMax = 0;



public:
	EnemyManager();
	~EnemyManager();
	list<EnemyShip*> enemyShips;
	void spawnRandom(float enemyCD);
	// control enemies' behaviors during their lifetime
	void update();

};