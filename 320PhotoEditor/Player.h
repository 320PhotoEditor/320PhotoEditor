#pragma once

#include <ctype.h>
#include "TOOL/MosaicTool.h"
#include "GUI/GUIElement.h"
#include <windows.h>

class Player
{
private:

	sf::RectangleShape shape;
	float moveSpeed;
	float accel;
	float decel;
	float currentSpeed;
	sf::Vector2f velocity;

	void initVar();
	void initShape();


public:
	Player();
	virtual ~Player();

	void updateInput();

	// target gives the player object access to some info about the window
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

