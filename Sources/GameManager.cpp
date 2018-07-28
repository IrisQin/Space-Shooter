#include "Simple2D.h"
#include "GameManager.h"
#include "SceneManager.cpp"
#include "Spaceship.h"
#include "Helper.h"
#include <iostream>
#include <vector> 
#include <type_traits>
using namespace Simple2D;

list<Sprite*> GameManager::playerBullets;
list<Sprite*> GameManager::enemyBullets;
list<Explosion*>  GameManager::explosions;

GameManager::GameManager():isKeyDown(170, false) {
	
	startTime = GetGameTime();
	string backGFile = "../../Content/Textures/StarLayer.png";
	backGroundCopy = new Sprite((float)SceneManager::getInstance().windowWidth, 0, backGFile, 3.f);
	windowBoundary = new Sprite(0, 0, SceneManager::getInstance().windowWidth, SceneManager::getInstance().windowHeight);

	//playerFactory = new PlayerFactory();
	playerShips.push_back(new PlayerShip(0.f, 100.f, 8.f,0,3));
	enemyManager = new EnemyManager();
}

//GameManager& GameManager::getInstance() {
//	static GameManager instance;
//	return instance;
//}

GameManager::~GameManager() {
	destroy(windowBoundary);
	destroy(backGroundCopy);
	destroy(enemyManager);
	if (!playerShips.empty()) {
		for (auto s : playerShips) destroy(s);
	}
	if (!playerBullets.empty()) {
		for (auto s : playerBullets ) destroy(s);
	}
	if (!enemyBullets.empty()) {
		for (auto s : enemyBullets) destroy(s);
	}
	if (!explosions.empty()) {
		for (auto s : explosions) destroy(s);
	}
}

void GameManager::update() {

	/*if (!pause) {
		points += 0.1;
		speed += 0.00032;
	}*/


	// move background in loop by using a copy
	Sprite* backGround = SceneManager::getInstance().backGround;
	backGround->move();
	backGroundCopy->move();
	int width = backGround->getWidth();
	if (backGround->getX() < -width + 10) backGround->setPosition((float)width, 0);
	if (backGroundCopy->getX() < -width + 10) backGroundCopy->setPosition((float)width, 0);
	backGround->draw();
	backGroundCopy->draw();

	
	input();
	

	// deal with enemy spawn
	float pastTime = GetGameTime() - startTime;
	if (pastTime > 3) {
		enemyManager->spawnRandom(2);
	}
	enemyManager->update();

	// deal with collision
	collision(&playerBullets,&enemyManager->enemyShips);
	collision(&enemyBullets, &playerShips);

	
	// when player die
	explode();
	if (playerShips.front()->life > 0) {
		playerShips.front()->draw();
	}
	else {
		
	}
	

	// death, move, delete outside, draw
	moveDieDraw(&playerBullets);
	moveDieDraw(&enemyBullets);
	moveDieDraw(&enemyManager->enemyShips);

	
	
}

template<class T1, class T2>
void GameManager::collision(list<T1*>* active, list<T2*>* passive) {
	for (auto i : *active) 
		for (auto j : *passive)
		{
			Sprite* is = i, *js = j;
			if (i->life && j->life && i->intersect(j)) 
				i->collide(j);
		}
}

template<class T>
void GameManager::moveDieDraw(list<T*>* i) {
	for (auto s = (*i).begin(); s != (*i).end(); ) {
		Sprite* curr = *s;
		curr->move();
		if (!curr->life || (!std::is_same<T, EnemyShip>::value && !curr->intersect(windowBoundary))) {
			s = (*i).erase(s);
			destroy(curr);
		}
		else {
			s++;
			curr->draw();
		}
	}
}

void GameManager::explode() {
	float currTime = GetGameTime();
	for (auto s = explosions.begin(); s != explosions.end(); ) {
		Explosion* curr = *s;
		float pastTime = currTime - curr->birthTime;
		if (pastTime >0.1f) {
			s = explosions.erase(s);
			destroy(curr);
		}
		else {
			s++;
			if (pastTime > 0.05f && curr->stage ==1) 
				curr->change2next();
			curr->draw();
		}
	}
}

// support long press
void GameManager::input() {
	PlayerShip* playerShip = playerShips.front();
	if (IsKeyPressed(KEY_SPACE) || isKeyDown[KEY_SPACE]) {
		playerShip->shoot();
		isKeyDown[KEY_SPACE] = true;
	}
	if (IsKeyPressed(KEY_UP_ARROW) || isKeyDown[KEY_UP_ARROW]) {
		playerShip->dirX = 0; playerShip->dirY = 1;
		playerShip->move(windowBoundary);
		isKeyDown[KEY_UP_ARROW] = true;
	}
	if (IsKeyPressed(KEY_DOWN_ARROW) || isKeyDown[KEY_DOWN_ARROW]) {
		playerShip->dirX = 0; playerShip->dirY = -1;
		playerShip->move(windowBoundary);
		isKeyDown[KEY_DOWN_ARROW] = true;
	}
	if (IsKeyPressed(KEY_LEFT_ARROW) || isKeyDown[KEY_LEFT_ARROW]) {
		playerShip->dirX = -1; playerShip->dirY = 0;
		playerShip->move(windowBoundary);
		isKeyDown[KEY_LEFT_ARROW] = true;
	}
	if (IsKeyPressed(KEY_RIGHT_ARROW) || isKeyDown[KEY_RIGHT_ARROW]) {
		playerShip->dirX = 1; playerShip->dirY = 0;
		playerShip->move(windowBoundary);
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
