#pragma once
#include "Simple2D.h"
#include "Spaceship.h"
#include "Factory.cpp"
#include <vector>
using namespace std;

class Game {
private:
	Game();
	~Game();
	float speed = 12,points = 0;
	bool pause = false;
	int ticks =0, bulletTicks = 0;
	vector<bool> isKeyDown;

	

	Sprite* backGround;
	Sprite* backGroundCopy;
	Sprite* windowBoundary;
	PlayerFactory* playerFactory;
	Spaceship* playerShip;
	
	void input();
	


public:
	static Game& getInstance();
	
	int width;
	int height;
	vector<Sprite*> playerBullets;
	vector<Sprite*> enemyBullets;
	void update();
};