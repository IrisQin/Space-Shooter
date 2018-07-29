#include "Simple2D.h"
#include "EnemyManager.h"
#include "SceneManager.cpp";
#include "Helper.h"
#include <iostream>
#include <vector>
using namespace std;

EnemyManager::EnemyManager() {
	spawnX = SceneManager::getInstance().rightBoundary;
	spawnYMax = SceneManager::getInstance().windowHeight;
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
	
	for (auto s : enemyShips ) {
		
		float pastTime = Simple2D::GetGameTime()-s->birthTime;
		
		s->shoot();
		
	}

	for (auto s : meteors) {

		float pastTime = Simple2D::GetGameTime() - s->birthTime;
		
		if (s->type == 0) {
			s->rotation++;
		}

	}
}

// TODO: more low-level enemies, less high-level
void EnemyManager::spawnRandom(float enemyCD) {
	if (Simple2D::GetGameTime() - spawnRandomTimer > enemyCD) {
		spawnRandomTimer = Simple2D::GetGameTime();

		EnemyShip* curr = new EnemyShip(spawnX, (float)randomInt(0, spawnYMax), randomInt(0,2));
		enemyShips.push_back(curr);

	}

}

// meteor groups
// 0: appear single, rotate 
// 1: 2*2 form a bigger
// 2: form meteor rain
// 3: appear single, 2 life
void EnemyManager::spawnMeteorRandom(float cd) {
	if (Simple2D::GetGameTime() - spawnMeteorRandomTimer > cd) {
		spawnMeteorRandomTimer = Simple2D::GetGameTime();
		int type = randomInt(0, 3);
		switch (type) {
			Meteor* m;
		case 0:
			m = new Meteor(spawnX, (float)randomInt(0, spawnYMax), 0);
			m->setImage(m->imageFiles[type]);
			meteors.push_back(m);
			break;
		case 1:
			m = new Meteor(spawnX, (float)randomInt(0, spawnYMax), 1);
			m->setImage(m->imageFiles[type]);
			meteors.push_back(m);
			break;
		case 2:
			m = new Meteor(spawnX, (float)randomInt(0, spawnYMax), 2);
			m->setImage(m->imageFiles[type]);
			meteors.push_back(m);
			break;
		case 3:
			m = new Meteor(spawnX, (float)randomInt(0, spawnYMax), 3);
			m->setImage(m->imageFiles[type]);
			meteors.push_back(m);
			break;
		default:cout << "type error" << endl; break;
		}
	
	
	
	}


}