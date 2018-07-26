#pragma once
#include "Sprite.h"
#include "Simple2D.h"
#include <vector>
using namespace std;

class Spaceship: public Sprite
{
private:
	vector<string> imageFiles;
	int level;
	bool _doubleGun = false;
	int _health;
	float _maxHealth;
public:
	Spaceship(float _x, float _y, float _speed);
	void takeDamages();
	void addHealth();
};