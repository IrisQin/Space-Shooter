#include "Sprite.h"
#include "Simple2D.h"
#include <iostream>
using namespace Simple2D;


Sprite::Sprite(float _x, float _y, float _speed) :x(_x), y(_y), speed(_speed) {
}


Sprite::Sprite(float _x, float _y, std::string& sImageFileName, float _speed ) :x(_x), y(_y), speed(_speed) {
	image = CreateImage(sImageFileName);
	GetImageSize(image, &width, &height);
}


Sprite::Sprite(float _x, float _y, int _width, int _height, float _speed) : x(_x), y(_y),width(_width), height(_height), speed(_speed) {
}

Sprite::~Sprite() {
	if (image != nullptr) {
		DestroyImage(image);
	}
	
}


void Sprite::setPosition(float _x, float _y) {
	x = _x;
	y = _y;
}

void Sprite::move(float offsetX, float offsetY){
	setPosition(x + offsetX*speed, y + offsetY*speed);
}

void Sprite::move(float offsetX, float offsetY, Sprite* boundary) {
	float p1 = boundary->getX();
	float p2 = boundary->getY();
	float p3 = p1 + boundary->getWidth() - width;
	float p4 = p2 + boundary->getHeight() - height;
	float targetX = x + offsetX*speed;
	float targetY = y + offsetY*speed;
	if(targetX>p1 && targetY>p2 && targetX<p3 && targetY<p4) setPosition(targetX, targetY);
}

void Sprite::draw(float fRotation, float fScale){
	DrawImage(image, x+ width/2, y+ height/2, fRotation, fScale);
}

void Sprite::changeImage(std::string& sImageFileName){
	DestroyImage(image);	
	image = CreateImage(sImageFileName);
	GetImageSize(image, &width, &height);
}

bool Sprite::intersect(Sprite* s) {
	return !((x + width < s->x) || (y > s->y+s->height) || (s->x+s->width < x) || (s->y > y+height));
}

float Sprite::getX() {
	return x;
}

float Sprite::getY() {
	return y;
}

int Sprite::getWidth() {
	return width;
}

int Sprite::getHeight() {
	return height;
}
