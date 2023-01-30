#pragma once

#include "GUIElement.h"

class ButtonElement : public GUIElement
{

public:

	typedef enum
	{
		UP,
		DOWN,
		OVER
	} ButtonState;

	ButtonElement(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);

	~ButtonElement();

private:

	sf::Vector2i cursorPos;

	sf::Texture* up;
	sf::Texture* down;
	sf::Texture* over;

	sf::Sprite* sprite;

    ButtonState buttonState;
};

