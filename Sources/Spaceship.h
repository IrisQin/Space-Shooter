#pragma once
#include "Sprite.h"
#include "Simple2D.h"
#include "Helper.h"
#include <vector>
using namespace std;

class Spaceship: public Sprite
{
protected:
	vector<string> imageFiles;
	int level = 0;
	float shootCD = 0.3f;
	float shootTimer = 0;
	float lowBulletSpeed = 10.f;
	float highBulletSpeed = 20.f;
public:
	Spaceship(float _x, float _y, float _speed, int _level = 0, int _life = 1);
	virtual void shoot()=0;
	bool beCollided();
	//void takeDamages();
	//void addHealth();
};


class PlayerShip : public Spaceship {
public:
	PlayerShip(float _x, float _y, float _speed, int _level = 0, int _life = 1);
	void shoot();


};

class EnemyShip : public Spaceship {
public:
	EnemyShip(float _x, float _y, int _level = 0, int _life = 1);
	float birthTime;
	void shoot();

};