#pragma once

#include "GUIElement.h"

class PanelElement : public GUIElement
{
public:

	PanelElement(sf::Texture* texture);

	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);

private:

	sf::Sprite* sprite;

};

