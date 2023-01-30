#include "ButtonElement.h"

//TODO: fix issues where texture not updating

ButtonElement::ButtonElement(sf::Texture* up, sf::Texture* down, sf::Texture* over) :  up(up), down(down), over(over)
{
	sprite = new sf::Sprite(*up);

	setDrawable(sprite);
	setVisible(true);

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
		if (isCursorOver(cursorPos))
		{
			sprite->setTexture(*over);
			buttonState = OVER;
		}
		else
		{
			sprite->setTexture(*up);
			buttonState = UP;
		}
	}
}

void ButtonElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
	if (isCursorOver(cursorPos) && buttonState != DOWN)
	{
		sprite->setTexture(*over);
		buttonState = OVER;
	}
	else
	{
		sprite->setTexture(*up);
		buttonState = UP;
	}

}

void ButtonElement::setSize(sf::Vector2f size)
{
	sf::Vector2u windowSize = container->getRenderWindow()->getSize();
	float ySize = container->getSize().y * windowSize.y;
	//using the y size so that ther is no aspect ratio resizing
	sf::Vector2f containerSize(ySize, ySize);

	sprite->setScale(size * containerSize / sprite->getTexture()->getSize());

	//properly store the size with the aspect ratio in mind
	this->size = { size.x * windowSize.y / windowSize.x, size.y };
}

void ButtonElement::setPosition(sf::Vector2f pos)
{
	sf::Vector2f containerSize = container->getSize() * container->getRenderWindow()->getSize();
	sf::Vector2f position = pos + container->getPosition();
	sprite->setPosition(containerSize * position);
	this->pos = pos;
}
