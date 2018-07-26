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
	Sprite backG(0, 0, backGFile);
	int backGWidth = backG.getWidth();
	int backGHeight = backG.getHeight();
	Window* pWindow = CreateWindow("ShooterGame", backGWidth, backGHeight);

	vector<bool> isKeyDown(170, false);

	Game game;


	while (!ShouldWindowClose(pWindow))
	{
		

		
		if (IsKeyPressed(KEY_UP_ARROW)|| isKeyDown[KEY_UP_ARROW]) {
			game.spaceship->move(0, 1, backG);
			isKeyDown[KEY_UP_ARROW] = true;
		}
		if (IsKeyPressed(KEY_DOWN_ARROW) || isKeyDown[KEY_DOWN_ARROW]) {
			game.spaceship->move(0, -1, backG);
			isKeyDown[KEY_DOWN_ARROW] = true;
		}
		if (IsKeyPressed(KEY_LEFT_ARROW) || isKeyDown[KEY_LEFT_ARROW]) {
			game.spaceship->move(-1, 0, backG);
			isKeyDown[KEY_LEFT_ARROW] = true;
		}
		if (IsKeyPressed(KEY_RIGHT_ARROW) || isKeyDown[KEY_RIGHT_ARROW]) {
			game.spaceship->move(1, 0, backG);
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



		backG.draw();
		game.spaceship->draw();
		RefreshWindowBuffer(pWindow);
	}

	DestroyWindow(pWindow);

}


