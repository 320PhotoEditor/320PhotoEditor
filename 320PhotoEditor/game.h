#pragma once

#include <ctype.h>
#include "TOOL/MosaicTool.h"
#include "GUI/GUIElement.h"
#include <windows.h>

class game
{
private:

	sf::VideoMode vm;
	sf::RenderWindow* window;
	bool endGame;

	//Initialize game variables
	void initVar();
	//Initialize game window
	void initWin();

public:
	//Constructor; Destructor
	game();
	~game();


	//Functions
	void update();
	void render();

};

