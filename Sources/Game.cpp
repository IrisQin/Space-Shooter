#include "Simple2D.h"
#include "Game.h"
#include "Spaceship.h"
#include <vector>
using namespace std;

Game::Game() {
	spaceship = new Spaceship(0.f, 100.f, 5);

}

Game::~Game() {
	delete spaceship;
}

void Game::update() {
	if (!pause) {
		points += 0.1;
		speed += 0.00032;
	}

	//manageShoots();
	//manageObstacles();
	spaceship->draw();

	if (pause) {
		ticks++;
	}
}

void Game::shoot() {
	int lspeed;
	
	if (_laserTicks > lspeed) {
		lasers.push_back(Laser((spaceship->getX() + spaceship->getGuns().x), (spaceship->getY() + spaceship->getGuns().y), Bonus::getColorLaser(_typeBonus)));
		if (spaceship->hasDoubleGun()) {
			lasers.push_back(Laser((spaceship->getX() + spaceship->getGuns().x), (spaceship->getY() + spaceship->getGuns().z), Bonus::getColorLaser(_typeBonus)));
			_laserTicks = -lspeed;
		}
		else {
			_laserTicks = 0;
		}
		
	}
}