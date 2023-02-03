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

		updateFunc(this, DOWN);
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

			updateFunc(this, OVER);
		}
		else
		{
			sprite->setTexture(*up);
			buttonState = UP;

			updateFunc(this, UP);
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
	//just need y size as were correcting for aspect ratio
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f containerSize = container->getSize() * windowSize;

	sprite->setScale(size * containerSize / sprite->getTexture()->getSize());

	this->size = size;
}

void ButtonElement::setPosition(sf::Vector2f pos)
{
	//just need y size as were correcting for aspect ratio
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f containerSize = container->getSize() * windowSize;
	sf::Vector2f position = pos + container->getPosition();

	sprite->setPosition(containerSize * position);
	this->pos = pos;
}

ButtonElement::~ButtonElement()
{
	delete sprite;
}
