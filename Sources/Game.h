#pragma once
#include "Simple2D.h"
#include "Spaceship.h"
#include <vector>
using namespace std;

class Game {
private:
	float speed;
	
	//vector<Bullet> bullets;
	//vector< ? > obstacles ? ;

public:
	Game();
	~Game();
	Spaceship* spaceship;
	//void moveBackground();

};