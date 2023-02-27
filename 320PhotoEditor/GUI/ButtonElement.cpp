#include "ButtonElement.h"

//TODO: fix issues where texture not updating

ButtonElement::ButtonElement(sf::Texture* up, sf::Texture* down, sf::Texture* over, bool toggle) :  up(up), down(down), over(over)
{
	sprite = new sf::Sprite(*up);

	setDrawable(sprite);
	setVisible(true);

	buttonState = UP;

	this->toggle = toggle;
}

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	if (isCursorOver(cursorPos))
	{
		if (toggle)
		{
			if (buttonState == DOWN)
			{
				sprite->setTexture(*up);
				buttonState = UP;
				updateFunc(this, UP);
			}
			else
			{
				sprite->setTexture(*down);
				buttonState = DOWN;
				updateFunc(this, DOWN);
			}
		}
		else
		{
			sprite->setTexture(*down);
			buttonState = DOWN;

			updateFunc(this, DOWN);
		}
	}
}

void ButtonElement::mouseReleased(sf::Mouse::Button button)
{
	if (toggle)
	{
		return;
	}

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
	if (toggle)
	{
		return;
	}

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
	sf::Vector2u windowSize = container->getRenderWindow()->getSize();

	float aspect = (float)windowSize.x / (float)windowSize.y;

	sf::Vector2f position = pos * container->getSize() + container->getPosition();
	position.x /= aspect;

	sprite->setPosition(position * windowSize);
	this->pos = pos;
}

ButtonElement::~ButtonElement()
{
	delete sprite;
}
