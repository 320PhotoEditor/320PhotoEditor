#pragma once

#include "../Common.h"
#include "GUIContainer.h"

class GUIContainer;

class GUIElement
{
public:

	GUIElement(GUIContainer* parent);

	virtual void render() {};
	void _render();

	virtual void mousePressed(sf::Mouse::Button button) {};
	virtual void mouseReleased(sf::Mouse::Button button) {};
	virtual void mouseMoved(sf::Vector2i pos) {};

	void setVisible(bool visible);

	//sets size relative to parent gui
	void setSize(sf::Vector2f size);

	//set position relative to parent gui
	void setPosition(sf::Vector2f pos);

	void setParent(GUIContainer* parent);

private:
	bool isCursorOver(sf::Vector2i cursorPos);

	sf::Sprite sprite;

	sf::Vector2f pos;
	sf::Vector2f size;

	bool visible;

	GUIContainer* parent;
};

