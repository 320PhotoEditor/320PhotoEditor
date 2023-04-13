#pragma once

#include "GUIElement.h"

class ColorPickerElement : public GUIElement
{
public:

	ColorPickerElement();

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);

	sf::Color getPickedColor();
	void setPickedColor(sf::Color color);

	void setLightness(float lightness);
	float getLightness();

	void setTransparency(float transparency);
	float getTransparency();

	void calcColor();

private:

	sf::Vector2i cursorPos;
	sf::Vector2f savedPos;

	float lightness;
	float transparency;

	bool dragging = false;

	sf::Sprite* sprite;

	sf::Color pickedColor;
	sf::Texture img;

};

