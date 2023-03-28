#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"

class WarpTool : public Tool
{
public:

	WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	//returns the indexes for the control point over the cursor
	//-1, -1 being no control point selected
	sf::Vector2i selectControlPoint(sf::Vector2i cursorPos);

private:

	std::vector<std::vector<sf::Vector2f>> controlPoints;

	Layer* layer;
};
