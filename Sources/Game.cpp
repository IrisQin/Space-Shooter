#include "Simple2D.h"
#include "Game.h"
#include "Spaceship.h"
#include <iostream>
#include <vector>
using namespace Simple2D;


Game::Game():isKeyDown(170, false) {

	string backGFile = "../../Content/Textures/StarLayer.png";
	backGround = new Sprite(0, 0, backGFile, 3);
	width = backGround->getWidth();
	height = backGround->getHeight();
	backGroundCopy = new Sprite(width, 0, backGFile, 3.f);
	windowBoundary = new Sprite(0, 0, width, height);

	playerFactory = new PlayerFactory();
	playerShip = playerFactory->createShip();
}

Game& Game::getInstance() {
	static Game instance;
	return instance;
}

Game::~Game() {
	if(playerShip) delete playerShip;
	if (playerFactory) delete playerFactory;
	if (windowBoundary) delete windowBoundary;
	if (backGround) delete backGround;
	if (backGroundCopy) delete backGroundCopy;
}

void Game::update() {

	if (!pause) {
		points += 0.1;
		speed += 0.00032;
	}

	input();

	//manageShoots();
	//manageObstacles();

	// move background in loop by using a copy
	backGround->move(-1, 0);
	backGroundCopy->move(-1, 0);
	if (backGround->getX() < -width + 10) backGround->setPosition((float)width, 0);
	if (backGroundCopy->getX() < -width + 10) backGroundCopy->setPosition((float)width, 0);
	backGround->draw();
	backGroundCopy->draw();





	playerShip->draw();
	for (auto s = playerBullets.begin(); s != playerBullets.end(); ){
		Sprite* curr = *s;
		curr->move(1, 0);
		if (!curr->intersect(windowBoundary)){
			s = playerBullets.erase(s);
			delete curr;
		}
		else {
			s++;
			curr->draw();
		}
	}
	cout << playerBullets.size()<<endl;

	if (pause) {
		ticks++;
	}
}

// support long press
void Game::input() {
	
	if (IsKeyPressed(KEY_SPACE) || isKeyDown[KEY_SPACE]) {
		playerShip->shoot();
		isKeyDown[KEY_SPACE] = true;
	}
	if (IsKeyPressed(KEY_UP_ARROW) || isKeyDown[KEY_UP_ARROW]) {
		playerShip->move(0, 1, windowBoundary);
		isKeyDown[KEY_UP_ARROW] = true;
	}
	if (IsKeyPressed(KEY_DOWN_ARROW) || isKeyDown[KEY_DOWN_ARROW]) {
		playerShip->move(0, -1, windowBoundary);
		isKeyDown[KEY_DOWN_ARROW] = true;
	}
	if (IsKeyPressed(KEY_LEFT_ARROW) || isKeyDown[KEY_LEFT_ARROW]) {
		playerShip->move(-1, 0, windowBoundary);
		isKeyDown[KEY_LEFT_ARROW] = true;
	}
	if (IsKeyPressed(KEY_RIGHT_ARROW) || isKeyDown[KEY_RIGHT_ARROW]) {
		playerShip->move(1, 0, windowBoundary);
		isKeyDown[KEY_RIGHT_ARROW] = true;
	}
	if (IsKeyReleased(KEY_SPACE)) {
		isKeyDown[KEY_SPACE] = false;
	}
	if (IsKeyReleased(KEY_UP_ARROW)) {
		isKeyDown[KEY_UP_ARROW] = false;
	}
	if (IsKeyReleased(KEY_DOWN_ARROW)) {
		isKeyDown[KEY_DOWN_ARROW] = false;
	}
	if (IsKeyReleased(KEY_LEFT_ARROW)) {
		isKeyDown[KEY_LEFT_ARROW] = false;
	}
	if (IsKeyReleased(KEY_RIGHT_ARROW)) {
		isKeyDown[KEY_RIGHT_ARROW] = false;
	}
}
