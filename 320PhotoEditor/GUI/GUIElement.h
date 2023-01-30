#pragma once

#include "../Common.h"
#include "GUIContainer.h"

class GUIContainer;

//base class for any gui element
class GUIElement
{
public:

	//internal render function, do not use
	void _render();

	virtual void mousePressed(sf::Mouse::Button button) {};
	virtual void mouseReleased(sf::Mouse::Button button) {};
	virtual void mouseMoved(sf::Vector2i pos) {};

	void setVisible(bool visible);

	//sets size relative to parent gui
	virtual void setSize(sf::Vector2f size) = 0;

	//set position relative to parent gui
	virtual void setPosition(sf::Vector2f pos) = 0;

	void setContainer(GUIContainer* container);

	bool isCursorOver(sf::Vector2i cursorPos);

	void setUpdateFunction(std::function<void(GUIElement*, int)> updateFunc);

protected:

	GUIElement()
	{
		drawable = nullptr;
		container = nullptr;
		visible = false;
		updateFunc = nullptr;
	}

	void setDrawable(sf::Drawable* drawable);

	sf::Drawable* drawable;
	GUIContainer* container;

	sf::Vector2f pos;
	sf::Vector2f size;


	std::function<void(GUIElement*, int)> updateFunc;

private:

	bool visible;
};
