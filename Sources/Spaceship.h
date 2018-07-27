#pragma once
#include "Sprite.h"
#include "Simple2D.h"
#include <vector>
using namespace std;

class Spaceship: public Sprite
{
protected:
	vector<string> imageFiles;
	int level = 0;
	int health = 0;
	float maxHealth = 0;
public:
	Spaceship(float _x, float _y, float _speed, int _level = 0);
	virtual void shoot()=0;
	//void takeDamages();
	//void addHealth();
};


class PlayerShip : public Spaceship {
public:
	PlayerShip(float _x, float _y, float _speed, int _level = 0);
	void shoot();


};

class EnemyShip : public Spaceship {
public:
	EnemyShip(float _x, float _y, float _speed, int _level = 0);
	void shoot();

};