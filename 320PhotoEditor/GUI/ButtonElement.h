#pragma once

#include "GUIElement.h"

class ButtonElement : public GUIElement
{

public:

	ButtonElement(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

private:

	sf::Vector2i cursorPos;

	sf::Texture* up;
	sf::Texture* down;
	sf::Texture* over;

	sf::Sprite* sprite;

	enum {
		UP,
		DOWN,
		OVER
	} buttonState;
};

