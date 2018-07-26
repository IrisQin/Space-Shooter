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