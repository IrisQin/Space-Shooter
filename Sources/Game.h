#pragma once
#include "Simple2D.h"
#include "Spaceship.h"
#include <vector>
using namespace std;

class Game {
private:
	float speed = 12,points = 0;
	bool pause = false;
	int ticks =0, bulletTicks = 0;
	//vector<Bullet> bullets;
	//vector< ? > obstacles ? ;

public:
	Game();
	~Game();
	Spaceship* spaceship;
	void update();
	void shoot();

};