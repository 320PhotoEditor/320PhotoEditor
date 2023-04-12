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
	

	void initVar();
	void initShape();


public:
	sf::Vector2f velocity;
	
	Player();
	virtual ~Player();
	
	void updateInput();
	void playerBounce(sf::Vector2f currentVel);
	void bounceOffPixel(sf::Vector2f playerVel, sf::Vector2f impulse, sf::Vector2f playerSize);

	sf::RectangleShape& getCurrShape();

	void playerWindowColl(sf::RenderTarget* target);
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

