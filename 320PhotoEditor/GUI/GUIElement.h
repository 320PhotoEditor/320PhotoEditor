#pragma once

#include "../Common.h"
#include "GUIContainer.h"

class GUIContainer;

//used from creating a type that we can draw with and use the transform functions
//example using it on sf::Sprite or sf::Text
class DrawTransformWrapper
{
public:
	template<class T, typename = std::enable_if_t<
		std::is_base_of<sf::Drawable, T>::value &&
		std::is_base_of<sf::Transformable, T>::value>>
	static DrawTransformWrapper* CreateWrapper(T* obj)
	{
		return new DrawTransformWrapper(dynamic_cast<sf::Drawable*>(obj), dynamic_cast<sf::Transformable*>(obj));
	}

	sf::Drawable* drawable;
	sf::Transformable* transformable;

private:

	DrawTransformWrapper(sf::Drawable* drawable, sf::Transformable* transformable) {
		this->drawable = drawable;
		this->transformable = transformable;
	}
};

//base class for any gui element
class GUIElement
{
public:

	template<class T>
	GUIElement(T* drawtransform)
	{
		this->drawtransform = DrawTransformWrapper::CreateWrapper<T>(drawtransform);
	}

	//internal render function, do not use
	void _render();

	virtual void mousePressed(sf::Mouse::Button button) {};
	virtual void mouseReleased(sf::Mouse::Button button) {};
	virtual void mouseMoved(sf::Vector2i pos) {};

	void setVisible(bool visible);

	//sets scale relative to parent gui
	void setScale(sf::Vector2f scale);

	//set position relative to parent gui
	void setPosition(sf::Vector2f pos);

	void setContainer(GUIContainer* container);

	bool isCursorOver(sf::Vector2i cursorPos);

	DrawTransformWrapper* drawtransform;

private:

	sf::Vector2f pos;
	sf::Vector2f scale;

	bool visible;

	GUIContainer* container;
};
