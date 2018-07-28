#include "Sprite.h"
#include "Spaceship.h"
#include "Simple2D.h"
#include "GameManager.h"
#include "Helper.h"
#include <iostream>
using namespace Simple2D;

Spaceship::Spaceship(float _x, float _y, float _speed, int _level, int _life) : Sprite(_x,_y,_speed, _life){
	level = _level;
}

//bool Spaceship::collide(Sprite* s) { 
//	s->beCollided();
//	return --life; 
//};

bool Spaceship::beCollided() {
	if (life == 1) {
	// create explosion
		string file = "../../Content/Textures/Explosion_1.png";
		Explosion* e = new Explosion(0, 0,file);
		e->setPosition(x+width/2-e->getWidth()/2, y+ height / 2 - e->getHeight() / 2);
		GameManager::explosions.push_back(e);
	}
	return --life;
};
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


PlayerShip::PlayerShip(float _x, float _y, float _speed, int _level, int _life) :Spaceship(_x, _y, _speed,_level,_life) {
	imageFiles.push_back("../../Content/Textures/Player_1.png");
	imageFiles.push_back("../../Content/Textures/Player_2.png");
	imageFiles.push_back("../../Content/Textures/Player_3.png");
	image = CreateImage(imageFiles[_level]);
	GetImageSize(image, &width, &height);
	dirX = 1.f;
}

void PlayerShip::shoot() {
	if (GetGameTime() - shootTimer > shootCD) {
		shootTimer = GetGameTime();
		
		string file = "../../Content/Textures/PlayerBullet.png";
		Sprite* bullet = new Sprite(0, 0, file, lowBulletSpeed);
		bullet->dirX = 1; bullet->dirY = 0;
		GameManager::playerBullets.push_back(bullet);

		float bulletX = x + width;
		float bulletY = y + height / 2 - bullet->getHeight() / 2;
		bullet->setPosition(bulletX, bulletY);
		if (level == 1) {
			bullet->speed = highBulletSpeed;
		}
		else if (level == 2) {
			bullet->speed = highBulletSpeed;
			bullet->setPosition(bulletX, y + height / 2 - bullet->getHeight() / 2 - 3);
			Sprite* bullet2 = new Sprite(bulletX, y + height / 2 + 3, file, highBulletSpeed);
			bullet2->dirX = 1; bullet2->dirY = 0;
			GameManager::playerBullets.push_back(bullet2);
		}
	}
}

EnemyShip::EnemyShip(float _x, float _y,int _level,int _life) :Spaceship(_x, _y, 5, _level,_life) {
	imageFiles.push_back("../../Content/Textures/Enemy_1.png");
	imageFiles.push_back("../../Content/Textures/Enemy_2.png");
	imageFiles.push_back("../../Content/Textures/Enemy_3.png");
	image = CreateImage(imageFiles[_level]);
	GetImageSize(image, &width, &height);
	birthTime = GetGameTime();
	life = level + 1;
	shootCD = 1.3f;
	lowBulletSpeed = 7.f;
	highBulletSpeed = 10.f;
}

void EnemyShip::shoot() {
	if (GetGameTime() - shootTimer > shootCD) {
		shootTimer = GetGameTime();

		string file = "../../Content/Textures/EnemyBullet.png";
		Sprite* bullet = new Sprite(0, 0, file, lowBulletSpeed);
		bullet->rotation = 180.f;
		GameManager::enemyBullets.push_back(bullet);

		float bulletX = x - bullet->getWidth();
		float bulletY = y + height / 2 - bullet->getHeight() / 2;
		bullet->setPosition(bulletX, bulletY);
		if (level == 1) {
			bullet->speed = highBulletSpeed;
		}
		else if (level == 2) {
			bullet->speed = highBulletSpeed;
			bullet->setPosition(bulletX, y + height / 2 - bullet->getHeight() / 2 - 3);
			Sprite* bullet2 = new Sprite(bulletX, y + height / 2 + 3, file, highBulletSpeed);
			bullet2->rotation = 180.f;
			GameManager::enemyBullets.push_back(bullet2);
		}
	}
}