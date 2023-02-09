#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"

class PaintTool : public Tool
{
public:

	PaintTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	void buttonPressed(GUIElement* button, int status);

private:

	void paint();

	ButtonElement* color1Button;
	ButtonElement* color2Button;
	ButtonElement* color3Button;

	bool isPainting = false;

	sf::Color paintColor;

	sf::Vector2i cursorPos;
	sf::Vector2i lastCursorPos;

	Layer* layer;
};
