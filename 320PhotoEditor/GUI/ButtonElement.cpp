#include "ButtonElement.h"

ButtonElement::ButtonElement(const sf::Texture& up, const sf::Texture& down, const sf::Texture& over) : GUIElement(new sf::Sprite(up)), up(&up), down(&down), over(&over)
{
	setVisible(true);
	sprite = (sf::Sprite*)drawtransform;
}

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	if (isCursorOver(cursorPos))
	{
		sprite->setTexture(*down);
		isDown = true;
	}
}

void ButtonElement::mouseReleased(sf::Mouse::Button button)
{
	if (isDown)
	{
		sprite->setTexture(*up);
	}
	isDown = false;
}

void ButtonElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
	if (isCursorOver(cursorPos) && !isDown)
	{
		std::cout << "wat" << std::endl;
		sprite->setTexture(*over);
	}
}
