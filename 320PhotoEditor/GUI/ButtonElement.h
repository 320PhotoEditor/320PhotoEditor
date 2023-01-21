#pragma once

#include "GUIElement.h"

class ButtonElement : public GUIElement
{

public:

	ButtonElement(GUIContainer* container, sf::Texture* up, sf::Texture* down, sf::Texture* over, sf::Vector2f pos, sf::Vector2f size);
	ButtonElement(GUIContainer* container, std::string up, std::string down, std::string over, sf::Vector2f pos, sf::Vector2f size);

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

private:

	sf::Vector2i cursorPos;

	bool isDown = false;

	sf::Texture* up;
	sf::Texture* down;
	sf::Texture* over;
};

