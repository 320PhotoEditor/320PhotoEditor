#include "GUIElement.h"

void GUIElement::_render()
{
	if (visible)
	{
		container->getRenderWindow()->draw(*drawtransform->drawable);
	}
}

void GUIElement::setVisible(bool visible)
{
	this->visible = visible;
}

void GUIElement::setSize(sf::Vector2f size)
{
	drawtransform->transformable->setScale(size);
	this->size = size;
}

void GUIElement::setPosition(sf::Vector2f pos)
{
	pos += container->getPosition();
	sf::Vector2u winSize = container->getRenderWindow()->getSize();

	drawtransform->transformable->setPosition({pos.x * winSize.x, pos.y * winSize.y});
	this->pos = pos;
}

void GUIElement::setContainer(GUIContainer* container)
{
	this->container = container;
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
