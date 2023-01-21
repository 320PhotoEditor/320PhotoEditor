#pragma once

#include "GUIElement.h"

class ButtonElement : public GUIElement
{

public:

	ButtonElement(sf::Texture down, sf::Texture up, sf::Texture over);

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

private:

};

