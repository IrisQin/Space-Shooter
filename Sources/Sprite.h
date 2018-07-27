#pragma once
#include "Simple2D.h"
#include <vector>
using namespace std;

class Sprite
{
protected:
	// the position of the bottom-left point of the image in screen
	float x,y;
	// only set in constructor and when change image
	int width, height;
	Simple2D::Image* image;
	

public:
	Sprite(float _x, float _y, float _speed = 0);
	// sprite without an image at all. can't be drawed.
	Sprite(float _x, float _y, int _width, int _height, float _speed = 0);
	// sprite with an image when constructed
	Sprite(float _x, float _y, std::string& sImageFileName, float _speed = 0);
	~Sprite();

	float speed;

	void setPosition(float _x, float _y);
	void move(float offsetX, float offsetY);
	// move inside a specified boundary
	void move(float offsetX, float offsetY, Sprite* boundary);
	void draw(float fRotation = 0.0f, float fScale = 1.0f);
	void changeImage(std::string& sImageFileName);
	bool intersect(Sprite* s);

	// getters
	float getX();
	float getY();
	int getWidth();
	int getHeight();

}; 