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

	void initVar();
	void initShape();


public:
	Pixels();
	virtual ~Pixels();

	void update();
	void render(sf::RenderTarget& target);
};

