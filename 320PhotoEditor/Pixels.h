#pragma once

#include <ctype.h>
#include "TOOL/MosaicTool.h"
#include "GUI/GUIElement.h"
#include <windows.h>

class Pixels
{
private:
	sf::RectangleShape shape;
	float moveSpeed;
	float currentSpeed;
	

	void initVar();
	void initShape();


public:
	Pixels();
	virtual ~Pixels();

	sf::RectangleShape& getCurrShape();
	sf::Vector2f velocity;
	void bounceOffPLayer(sf::Vector2f pixelVel, sf::Vector2f impulse, sf::Vector2f pixelSize);
	void bounceOffWindow(sf::Vector2f currentVel);
	void pixelWindowColl(sf::RenderTarget* target);
	void update();
	void render(sf::RenderTarget& target);
};

