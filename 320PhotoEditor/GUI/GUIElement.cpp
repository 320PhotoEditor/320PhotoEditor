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

void GUIElement::setScale(sf::Vector2f scale)
{
	sf::Vector2f containerScale = container->getScale();
	drawtransform->transformable->setScale({scale.x * containerScale.x, scale.y * containerScale.y});
	this->scale = scale;
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
	float right = pos.x + scale.x;
	float top = pos.y;
	float bottom = pos.y + scale.y;

	return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}
