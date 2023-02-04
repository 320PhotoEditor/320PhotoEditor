#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"

class TestTool : public Tool
{
public:
	TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void start(Layer* layer);
	void stop() {};
	void run() {};

	void keyPressed(sf::Keyboard::Key key);

	void buttonPressed(GUIElement* button, int status) { }
private:

	Layer* layer;
};

