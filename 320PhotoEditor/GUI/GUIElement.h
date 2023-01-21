#pragma once

#include "../Common.h"
#include "GUIContainer.h"

class GUIContainer;

//base class for any gui element
class GUIElement
{
public:

	GUIElement() {};

	//add any additional things here that you want to render
	//runs directly after the base sprite is rendered
	virtual void render() {};
	
	//internal render function, do not use
	void _render();

	virtual void mousePressed(sf::Mouse::Button button) {};
	virtual void mouseReleased(sf::Mouse::Button button) {};
	virtual void mouseMoved(sf::Vector2i pos) {};

	void setVisible(bool visible);

	//sets size relative to parent gui
	void setSize(sf::Vector2f size);

	//set position relative to parent gui
	void setPosition(sf::Vector2f pos);

	void setContainer(GUIContainer* container);

	sf::Sprite* getSprite();
	void setSprite(sf::Sprite* sprite);

	bool isCursorOver(sf::Vector2i cursorPos);

private:

	sf::Sprite* sprite;

	sf::Vector2f pos;
	sf::Vector2f size;

	bool visible;

	GUIContainer* container;
};
