#pragma once

#include "Tool.h"

class TestTool : public Tool
{
public:
	TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void start(Layer* layer);
	void stop() {};
	void run() {};

	void keyPressed(sf::Keyboard::Key key);
private:

	Layer* layer;
};

