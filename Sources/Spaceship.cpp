#include "Sprite.h"
#include "Spaceship.h"
#include "Simple2D.h"
#include <iostream>
using namespace Simple2D;

string initSpaceshipFile = "../../Content/Textures/Player_1.png";

Spaceship::Spaceship(float _x, float _y, float _speed) : Sprite(_x,_y, initSpaceshipFile,_speed)
{
	imageFiles.push_back("../../Content/Textures/Player_1.png");
	imageFiles.push_back("../../Content/Textures/Player_2.png");
	imageFiles.push_back("../../Content/Textures/Player_3.png");
	_health = _maxHealth = 120;
	level = 0;
}



/*
* Remove health when the spaceship is hit
*/
void Spaceship::takeDamages()
{
	_health -= 30;
	if (_health <= 0) {
		_health = 0;
	}
}



/*
* Add health to the spaceship
*/
void Spaceship::addHealth()
{
	_health += 30;
	if (_health > _maxHealth) {
		_health = _maxHealth;
	}
}


