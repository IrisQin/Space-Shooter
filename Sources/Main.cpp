#include "Simple2D.h"
#include "Sprite.h"
#include "Spaceship.h"
#include "Game.h"
#include <iostream>
#include <direct.h>
using namespace Simple2D;


int main(int argc, char *argv[])
{
	
	Game& game = Game::getInstance();
	Window* pWindow = CreateWindow("ShooterGame", game.width, game.height);
	while (!ShouldWindowClose(pWindow))
	{
		game.update();
		RefreshWindowBuffer(pWindow);
	}

	DestroyWindow(pWindow);
	
}


