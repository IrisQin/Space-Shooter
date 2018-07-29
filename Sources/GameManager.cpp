#include "Simple2D.h"
#include "GameManager.h"
#include "SceneManager.cpp"
#include "Helper.h"
#include "Sprite.h"
#include <iostream>
#include <vector> 
#include <type_traits>


using namespace Simple2D;

float GameManager::speed;
list<Sprite*> GameManager::playerBullets;
list<Sprite*> GameManager::enemyBullets;
list<Explosion*>  GameManager::explosions;

GameManager::GameManager():isKeyDown(170, false) {
	startTime = GetGameTime();
	string backGFile = "../../Content/Textures/StarLayer.png";
	speed = SceneManager::getInstance().initSpeed;
	backGroundCopy = new Sprite((float)SceneManager::getInstance().windowWidth, 0, backGFile, speed);
	windowBoundary = new Sprite(0, 0, SceneManager::getInstance().rightBoundary, SceneManager::getInstance().windowHeight);
	playerShips.push_back(new PlayerShip(0.f, 100.f, 8.f,0,3));
	enemyManager = new EnemyManager();
	
}

GameManager::~GameManager() {
	destroy(windowBoundary);
	destroy(backGroundCopy);
	destroy(enemyManager);
	if (!playerShips.empty()) {
		for (auto s : playerShips) destroy(s);
		playerShips.clear();
	}
	if (!playerBullets.empty()) {
		for (auto s : playerBullets ) destroy(s);
		playerBullets.clear();
	}
	if (!enemyBullets.empty()) {
		for (auto s : enemyBullets) destroy(s);
		enemyBullets.clear();
	}
	if (!explosions.empty()) {
		for (auto s : explosions) destroy(s);
		explosions.clear();
	}
	if (!upgrades.empty()) {
		for (auto s : upgrades) destroy(s);
		upgrades.clear();
	}
 }

void GameManager::update() {

	speed += 0.001;
	moveBg();
	input();	

	// deal with object spawn
	float pastTime = GetGameTime() - startTime;
	if (pastTime > 5) {
		enemyManager->spawnRandom(4);
		enemyManager->spawnMeteorRandom(7);
		upgradeSpawn(10.f);
		

	}
	else if (pastTime > 2) {
		enemyManager->spawnRandom(5);
		enemyManager->spawnMeteorRandom(8);
	}

	enemyManager->update();
	




	// deal with collision
	collision(&playerBullets,&enemyManager->enemyShips);
	collision(&enemyBullets, &playerShips);
	collision(&enemyManager->enemyShips, &playerShips);
	collision(&playerShips, &upgrades);
	collision(&playerBullets, &enemyManager->meteors);
	collision(&enemyManager->meteors, &playerShips);
	collision(&enemyManager->meteors, &enemyManager->enemyShips);

	
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
	moveDieDraw(&enemyManager->meteors);
	moveDieDraw(&upgrades);

	
	
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
		if (!curr->life || !curr->intersect(windowBoundary)) { //(!std::is_same<T, EnemyShip>::value &&
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

void GameManager:: moveBg() {
	
	Sprite* backGround = SceneManager::getInstance().backGround;
	backGround->speed = speed;
	backGround->move();
	backGroundCopy->speed = speed;
	backGroundCopy->move();
	int width = backGround->getWidth();
	if (backGround->getX() < -width + 20) backGround->setPosition((float)width, 0);
	if (backGroundCopy->getX() < -width + 20) backGroundCopy->setPosition((float)width, 0);
	backGround->draw();
	backGroundCopy->draw();
}

void GameManager::upgradeSpawn(float cd) {
	if (Simple2D::GetGameTime() - upgradeSpawnTimer > cd) {
		upgradeSpawnTimer = Simple2D::GetGameTime();
		string file = "../../Content/Textures/Upgrade.png";
		Sprite* curr = new Sprite(SceneManager::getInstance().rightBoundary, (float)randomInt(0, SceneManager::getInstance().windowHeight), file ,speed);
		upgrades.push_back(curr);
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
