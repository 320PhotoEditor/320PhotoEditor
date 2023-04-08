#pragma once

#include "Player.h"

class game
{
private:

	sf::VideoMode vm;
	sf::RenderWindow* window;
	sf::Event ev;
	bool endGame;
	Player player;

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

