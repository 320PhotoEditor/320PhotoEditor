#include "ButtonElement.h"


ButtonElement::ButtonElement(sf::Texture* up, sf::Texture* down, sf::Texture* over) : GUIElement(new sf::Sprite(*up)), up(up), down(down), over(over)
{
	setVisible(true);
	sprite = (sf::Sprite*)drawtransform;
	buttonState = UP;
}

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	if (isCursorOver(cursorPos))
	{
		sprite->setTexture(*down);
		buttonState = DOWN;
	}
}

void ButtonElement::mouseReleased(sf::Mouse::Button button)
{
	if (buttonState == DOWN)
	{
		sprite->setTexture(*up);
	}
	buttonState = UP;
}

void ButtonElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
	if (isCursorOver(cursorPos) && buttonState != DOWN && buttonState != OVER)
	{
		sprite->setTexture(*over);
		buttonState = OVER;
	}
}
