#pragma once
#include "Simple2D.h"
#include "Spaceship.h"
#include "Factory.cpp"
#include "EnemyManager.h"
#include "Explosion.cpp"
#include "Helper.h"
#include <vector>
#include <list>
using namespace std;

class GameManager {
private:
	
	float speed = 12,points = 0, startTime;
	bool pause = false;
	vector<bool> isKeyDown;

	Sprite* backGroundCopy;
	Sprite* windowBoundary;

	list<PlayerShip*> playerShips;
	
	EnemyManager* enemyManager;

	void input();
	// call active's "collide()", call passive's "beCollided()"
	template<class T1, class T2>
	void collision(list<T1*>* active, list<T2*>* passive);
	template<class T>
	void moveDieDraw(list<T*>* i);
	void explode();


public:
	// singleton
	//static GameManager& getInstance();
	GameManager();
	~GameManager();
	
	static list<Sprite*> playerBullets;
	static list<Sprite*> enemyBullets;
	static list<Explosion*> explosions;
	// control all kinds of objects' behaviors according to game stage
	void update();
	
};