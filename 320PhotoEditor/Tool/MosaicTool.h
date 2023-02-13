#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"

class MosaicTool : public Tool
{
public:
	MosaicTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	//void keyPressed(sf::Keyboard::Key key);

	void buttonPressed(GUIElement* button, int status);
private:
	ButtonElement* selectButton;
	Layer* layer;
	sf::RenderWindow* newWindow;
};

