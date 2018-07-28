#pragma once
#include "Simple2D.h"
#include "Helper.h"
#include <vector>
using namespace std;

class Sprite
{
protected:
	// the position of the bottom-left point of the image in screen
	float x = 0,y = 0;
	// only set in constructor and when change image
	int width = 0, height = 0;
	Simple2D::Image* image = nullptr;
	// change to another image and stay at the same central point
	void changeImage(std::string& sImageFileName);

public:
	Sprite(float _x, float _y, float _speed = 0, int _life = 1);
	// sprite without an image at all. can't be drawed.
	Sprite(float _x, float _y, int _width, int _height, float _speed = 0);
	// sprite with an image when constructed
	Sprite(float _x, float _y, std::string& sImageFileName, float _speed = 0, int _life = 1);
	virtual ~Sprite();

	float speed = 0;
	int life = 1;
	float rotation = 0;
	float scale = 1;
	float dirX = -1, dirY = 0;

	void setPosition(float _x, float _y);
	void move();
	// move inside a specified boundary
	void move(Sprite* boundary);
	void draw();
	
	bool intersect(Sprite* s);
	// return the sprite itself is alive or not after collision
	virtual bool collide(Sprite* s) { s->beCollided(); return --life; };
	virtual bool beCollided() { return --life; };

	// getters
	float getX();
	float getY();
	int getWidth();
	int getHeight();

}; 