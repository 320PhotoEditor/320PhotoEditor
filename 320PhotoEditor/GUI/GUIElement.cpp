#include "GUIElement.h"

void GUIElement::_render()
{
	if (visible && drawable)
	{
		container->getRenderWindow()->draw(*drawable);
	}
}

void GUIElement::setVisible(bool visible)
{
	this->visible = visible;
}

void GUIElement::setContainer(GUIContainer* container)
{
	this->container = container;
}

bool GUIElement::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2f containerPos = container->getPosition();
	sf::Vector2f containerSize = container->getSize();
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f cPos = cursorPos / windowSize;

	float left = (pos.x * containerSize.x) + containerPos.x;
	float right = ((pos.x + size.x) * containerSize.x) + containerPos.x;
	float top = (pos.y * containerSize.y) + containerPos.y;
	float bottom = ((pos.y + size.y) * containerSize.y) + containerPos.y;

	return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}

void GUIElement::setUpdateFunction(std::function<void(GUIElement*, int)> updateFunc)
{
	this->updateFunc = updateFunc;
}

void GUIElement::setDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}
