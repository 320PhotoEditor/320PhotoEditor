#include "GUIElement.h"

GUIElement::GUIElement(GUIContainer* parent)
{
	this->parent = parent;
	visible = true;
}

void GUIElement::_render()
{
	if (visible)
	{
		parent->getRenderWindow()->draw(sprite);
		render();
	}
}

void GUIElement::setVisible(bool visible)
{
	this->visible = visible;
}

void GUIElement::setSize(sf::Vector2f size)
{
	sprite.setScale(size);
	this->size = size;
}

void GUIElement::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(parent->getPosition() + pos);
	this->pos = pos;
}

void GUIElement::setParent(GUIContainer* parent)
{
	this->parent = parent;
}

bool GUIElement::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2f cPos = parent->pixelToScreen(cursorPos);

	float left = pos.x;
	float right = pos.x + size.x;
	float top = pos.y;
	float bottom = pos.y + size.y;

	return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}
