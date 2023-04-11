#pragma once

#include "Player.h"
#include "Pixels.h"
#include <vector>

class game
{
private:

	sf::VideoMode vm;
	sf::RenderWindow* window;
	sf::Event ev;
	bool endGame;
	Player player;
	std::vector<Pixels> Pixel;

	float spawnTimeMax;
	float spawnTimer;
	int maxPixels;

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
	void spawnPixels();
	void playerPixelColl();

};

