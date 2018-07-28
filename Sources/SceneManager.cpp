#include "Simple2D.h"
#include "GameManager.h"
#include "Spaceship.h"
#include "Helper.h"
#include <iostream>
#include <vector> 
#include <type_traits>
using namespace Simple2D;

class SceneManager {
private:
	SceneManager() {
		string backGFile = "../../Content/Textures/StarLayer.png";
		backGround = new Sprite(0, 0, backGFile, 3);
		windowWidth = backGround->getWidth();
		windowHeight = backGround->getHeight();


	};
	~SceneManager() {
		destroy(gameManager);
		destroy(backGround);
	};

	enum Status
	{
		InMenu,
		Ready,
		InGame,
	};
	GameManager* gameManager;

	void input() {
		if (IsKeyPressed(KEY_SPACE)) {
			status = Ready;
		}

	}

public:
	// singleton
	static SceneManager& getInstance() {
		static SceneManager instance;
		return instance;
	}

	int windowWidth, windowHeight;
	Sprite* backGround;
	
	Status status = InMenu;

	void update() {
		switch (status) {
		case(InMenu):
			input(); break;
		case(Ready):
			gameManager = new GameManager(); status = InGame; break;
		case(InGame):
			gameManager->update();
		default:
			cout << "status error" << endl; break;
		}
	}


};