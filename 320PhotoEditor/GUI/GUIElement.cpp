#include "GUIElement.h"

void GUIElement::_render()
{
	if (visible)
	{
		if (sprite)
		{
			container->getRenderWindow()->draw(*sprite);
		}
		render();
	}
}

void GUIElement::setVisible(bool visible)
{
	this->visible = visible;
}

void GUIElement::setSize(sf::Vector2f size)
{
	sprite->setScale(size);
	this->size = size;
}

void GUIElement::setPosition(sf::Vector2f pos)
{
	sprite->setPosition(container->getPosition() + pos);
	this->pos = pos;
}

void GUIElement::setContainer(GUIContainer* container)
{
	this->container = container;
}

sf::Sprite* GUIElement::getSprite()
{
	return sprite;
}

void GUIElement::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

bool GUIElement::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2f cPos = container->pixelToScreen(cursorPos);


	//std::cout << cPos.x << " : " << cPos.y << std::endl;


	std::cout << size.x << " : " << size.y << std::endl;

	float left = pos.x;
	float right = pos.x + size.x;
	float top = pos.y;
	float bottom = pos.y + size.y;

	return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}
