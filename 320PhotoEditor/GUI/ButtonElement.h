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

	//when toggle is true, buttons toggle instead of being pressed once
	//over texture is not used when toggle is set to true
	ButtonElement(sf::Texture* up, sf::Texture* down, sf::Texture* over, bool toggle = false);

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

	bool toggle;
};

