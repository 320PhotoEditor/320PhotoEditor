#include "ButtonElement.h"

ButtonElement::ButtonElement(GUIContainer* container, const sf::Texture& up, const sf::Texture& down, const sf::Texture& over) : up(up), down(down), over(over)
{
	setSprite(new sf::Sprite(up));
	GUIElement(container, getSprite());
}

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	if (isCursorOver(cursorPos))
	{
		getSprite()->setTexture(down);
		isDown = true;
	}
}

void ButtonElement::mouseReleased(sf::Mouse::Button button)
{
	getSprite()->setTexture(up);
	isDown = false;
}

void ButtonElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
	if (isCursorOver(cursorPos) && !isDown)
	{
		getSprite()->setTexture(over);
	}
}
