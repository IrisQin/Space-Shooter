#pragma once
#include "Simple2D.h"
#include "EnemyManager.h"
#include "Explosion.cpp"
#include "Helper.h"
#include <vector>
#include <list>
using namespace std;

class GameManager {
private:
	
	float startTime;
	float upgradeSpawnTimer = 0;
	bool pause = false;
	vector<bool> isKeyDown;

	Sprite* backGroundCopy;
	Sprite* windowBoundary;

	list<PlayerShip*> playerShips;
	list<Sprite*> upgrades;
	EnemyManager *enemyManager;

	

	void input();
	// call active's "collide()", call passive's "beCollided()"
	template<class T1, class T2>
	void collision(list<T1*>* active, list<T2*>* passive);
	template<class T>
	void moveDieDraw(list<T*>* i);
	void explode();
	void upgradeSpawn(float cd);
	// move background in loop by using a copy
	void moveBg();

public:
	GameManager();
	~GameManager();
	
	
	static float speed;
	static list<Sprite*> playerBullets;
	static list<Sprite*> enemyBullets;
	static list<Explosion*> explosions;
	// control all kinds of objects' behaviors according to game stage
	void update();
	
};