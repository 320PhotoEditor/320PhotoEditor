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
	sf::Vector2f velocity;

	void initVar();
	void initShape();


public:
	Pixels();
	virtual ~Pixels();

	sf::RectangleShape& getCurrShape();

	void bounceOffPLayer(sf::Vector2f currentVel);
	void bounceOffWindow(sf::Vector2f currentVel);
	void pixelWindowColl(sf::RenderTarget* target);
	void update();
	void render(sf::RenderTarget& target);
};

