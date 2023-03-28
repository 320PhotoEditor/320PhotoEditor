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

private:

	void calcColor();

	sf::Vector2i cursorPos;
	sf::Vector2i savedPos;

	float lightness;

	bool dragging = false;

	sf::Sprite* sprite;

	sf::Color pickedColor;
	sf::Texture img;

};

