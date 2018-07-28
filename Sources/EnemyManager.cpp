#include "Simple2D.h"
#include "EnemyManager.h"
#include "Spaceship.h"
#include "Factory.cpp"
#include "GameManager.h"
#include "SceneManager.cpp"
#include "Helper.h"
#include <iostream>
#include <vector>
using namespace std;

EnemyManager::EnemyManager() {
	spawnX = SceneManager::getInstance().windowWidth + 100.f;	//100.f = bullet's max width
	spawnYMax = SceneManager::getInstance().windowHeight - 140.f;	//140.f = enemy's max height
}

EnemyManager::~EnemyManager() {
	if (!enemyShips.empty()) {
		for (auto s : enemyShips) destroy(s);
	}

}

//EnemyManager& EnemyManager::getInstance() {
//	static EnemyManager instance;
//	return instance;
//}

void EnemyManager::update() {
	for (auto s = enemyShips.begin(); s != enemyShips.end(); ) {
		EnemyShip* curr = *s;
		float pastTime = Simple2D::GetGameTime()-curr->birthTime;
		//destroy after a few seconds
		if (pastTime > 8) {
			s = enemyShips.erase(s);
			destroy(curr);
		}
		//deal with alive enemies
		else {
			s++;
			//control shoot,direction
			curr->shoot();
		}
	}
}

// TODO: more low-level enemies, less high-level
void EnemyManager::spawnRandom(float enemyCD) {
	if (Simple2D::GetGameTime() - spawnRandomTimer > enemyCD) {
		spawnRandomTimer = Simple2D::GetGameTime();

		EnemyShip* curr = new EnemyShip(spawnX, (float)randomInt(0,spawnYMax), randomInt(0,2));
		enemyShips.push_back(curr);

	}

}