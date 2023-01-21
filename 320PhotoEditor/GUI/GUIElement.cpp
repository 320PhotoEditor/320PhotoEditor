#include "GUIElement.h"

GUIElement::GUIElement(GUIContainer* container, sf::Sprite* sprite)
{
	this->container = container;
	visible = true;
	
}

void GUIElement::_render()
{
	if (visible)
	{
		container->getRenderWindow()->draw(*sprite);
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

void GUIElement::setParent(GUIContainer* container)
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

	float left = pos.x;
	float right = pos.x + size.x;
	float top = pos.y;
	float bottom = pos.y + size.y;

	return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}
