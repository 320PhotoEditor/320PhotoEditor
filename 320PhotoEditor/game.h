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
	sf::Event ev;
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
	const bool running() const;
	void pollEvents();
	void update();
	void render();

};

