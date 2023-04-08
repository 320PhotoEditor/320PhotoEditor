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

	void initVar();
	void initShape();


public:
	Player();
	virtual ~Player();

	void updateInput();
	void update();
	void render(sf::RenderTarget* target);

};

