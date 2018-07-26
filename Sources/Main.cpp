#include "Simple2D.h"
#include "Sprite.h"
#include "Spaceship.h"
#include "Game.h"
#include <iostream>
#include <direct.h>
using namespace Simple2D;


int main(int argc, char *argv[])
{
	
	string backGFile = "../../Content/Textures/StarLayer.png";
	Sprite backG1(0, 0, backGFile, 3);
	int backGWidth = backG1.getWidth();
	int backGHeight = backG1.getHeight();
	Sprite backG2(backGWidth, 0, backGFile, 3);
	Sprite window(0, 0, backGWidth, backGHeight);
	Window* pWindow = CreateWindow("ShooterGame", backGWidth, backGHeight);

	vector<bool> isKeyDown(170, false);

	Game game;


	while (!ShouldWindowClose(pWindow))
	{
		
		// move background in loop by using 2 images
		backG1.move(-1, 0);
		backG2.move(-1, 0);
		if (backG1.getX() < -backGWidth+10) backG1.setPosition(backGWidth, 0);
		if (backG2.getX() < -backGWidth+10) backG2.setPosition(backGWidth, 0);
		backG1.draw();
		backG2.draw();

		// input, support long press
		if (IsKeyPressed(KEY_UP_ARROW)|| isKeyDown[KEY_UP_ARROW]) {
			game.spaceship->move(0, 1, window);
			isKeyDown[KEY_UP_ARROW] = true;
		}
		if (IsKeyPressed(KEY_DOWN_ARROW) || isKeyDown[KEY_DOWN_ARROW]) {
			game.spaceship->move(0, -1, window);
			isKeyDown[KEY_DOWN_ARROW] = true;
		}
		if (IsKeyPressed(KEY_LEFT_ARROW) || isKeyDown[KEY_LEFT_ARROW]) {
			game.spaceship->move(-1, 0, window);
			isKeyDown[KEY_LEFT_ARROW] = true;
		}
		if (IsKeyPressed(KEY_RIGHT_ARROW) || isKeyDown[KEY_RIGHT_ARROW]) {
			game.spaceship->move(1, 0, window);
			isKeyDown[KEY_RIGHT_ARROW] = true;
		}
		if (IsKeyReleased(KEY_UP_ARROW)) {
			isKeyDown[KEY_UP_ARROW] = false;
		}
		if (IsKeyReleased(KEY_DOWN_ARROW)) {
			isKeyDown[KEY_DOWN_ARROW] = false;
		}
		if (IsKeyReleased(KEY_LEFT_ARROW)) {
			isKeyDown[KEY_LEFT_ARROW] = false;
		}
		if (IsKeyReleased(KEY_RIGHT_ARROW)) {
			isKeyDown[KEY_RIGHT_ARROW] = false;
		}


		game.update();

		
		
		RefreshWindowBuffer(pWindow);
	}

	DestroyWindow(pWindow);

}


