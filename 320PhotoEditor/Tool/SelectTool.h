#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"

class SelectTool : public Tool
{
public:

	SelectTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

private:

	int sign(int x)
	{
		return (x > 0) - (x < 0);
	}

	sf::Vector2i selectPos1;
	sf::Vector2i selectPos2;

	bool isSelecting = false;

	sf::Vector2i cursorPos;

	Layer* layer;
};
