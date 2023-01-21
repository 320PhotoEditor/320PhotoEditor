#include "ButtonElement.h"

ButtonElement::ButtonElement(sf::Texture down, sf::Texture up, sf::Texture over)
{
	GUIElement();
}

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	getSprite()->setTexture();
}

void ButtonElement::mouseReleased(sf::Mouse::Button button)
{
}

void ButtonElement::mouseMoved(sf::Vector2i pos)
{
}
