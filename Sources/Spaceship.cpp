#include "Sprite.h"
#include "Spaceship.h"
#include "Simple2D.h"
#include "Game.h"
#include <iostream>
using namespace Simple2D;

Spaceship::Spaceship(float _x, float _y, float _speed, int _level) : Sprite(_x,_y,_speed){
	level = _level;
}

/*
* Remove health when the spaceship is hit
*/
//void Spaceship::takeDamages()
//{
//	health -= 30;
//	if (health <= 0) {
//		health = 0;
//	}
//}



/*
* Add health to the spaceship
*/
//void Spaceship::addHealth()
//{
//	health += 30;
//	if (health > maxHealth) {
//		health = maxHealth;
//	}
//}


PlayerShip::PlayerShip(float _x, float _y, float _speed, int _level) :Spaceship(_x, _y, _speed,_level) {
	imageFiles.push_back("../../Content/Textures/Player_1.png");
	imageFiles.push_back("../../Content/Textures/Player_2.png");
	imageFiles.push_back("../../Content/Textures/Player_3.png");
	health = maxHealth = 3;
	image = CreateImage(imageFiles[_level]);
	GetImageSize(image, &width, &height);
}

void PlayerShip::shoot() {
	
	string file = "../../Content/Textures/PlayerBullet.png";
	Sprite* bullet = new Sprite(0, 0, file, 10.f);
	Game::getInstance().playerBullets.push_back(bullet);
	
	float bulletX = x + width + 3;
	float bulletY = y + height / 2 - bullet->getHeight() / 2;
	bullet->setPosition(bulletX, bulletY);
	if (level == 1) {
		bullet->speed = 20.f;
	}
	else if (level == 2) {
		bullet->speed = 20.f;
		bullet->setPosition(bulletX, y + height / 2 - bullet->getHeight() / 2 - 3);
		Sprite* bullet2 = new Sprite(bulletX, y + height / 2 + 3, file, 20.f);
		Game::getInstance().playerBullets.push_back(bullet2);
	}
}

EnemyShip::EnemyShip(float _x, float _y, float _speed, int _level) :Spaceship(_x, _y, _speed, _level) {
	imageFiles.push_back("../../Content/Textures/Enemy_1.png");
	imageFiles.push_back("../../Content/Textures/Enemy_2.png");
	imageFiles.push_back("../../Content/Textures/Enemy_3.png");
	health = maxHealth = _level+1;
	image = CreateImage(imageFiles[_level]);
	GetImageSize(image, &width, &height);
}

void EnemyShip::shoot() {

}