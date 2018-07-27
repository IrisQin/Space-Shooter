
#include "Spaceship.h"
//#include "Explosion.h"



class Factory		
{
public:

	virtual Spaceship *createShip() = 0;
	//virtual Explosion *createExplosion() = 0;
};

class PlayerFactory :public Factory	
{
public:



	Spaceship *createShip()
	{
		return new PlayerShip(0.f, 100.f, 5);
	}

};

class EnemyFactory :public Factory	
{
public:


	Spaceship *createShip(float _x, float _y, float _speed)
	{
		return new EnemyShip(_x,_y,_speed);
	}
};
