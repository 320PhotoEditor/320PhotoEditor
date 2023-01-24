#pragma once

#include "GUIElement.h"

class ButtonElement : public GUIElement
{

public:

	ButtonElement(const sf::Texture& up, const sf::Texture& down, const sf::Texture& over);

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

private:

	sf::Vector2i cursorPos;

	const sf::Texture* up;
	const sf::Texture* down;
	const sf::Texture* over;

	sf::Sprite* sprite;

	enum {
		UP,
		DOWN,
		OVER
	} buttonState;
};

