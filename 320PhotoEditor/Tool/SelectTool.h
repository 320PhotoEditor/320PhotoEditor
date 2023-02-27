#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "../AssetManager.h"

class SelectTool : public Tool
{
public:

	SelectTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	void buttonPressed(GUIElement* button, int status);

private:

	void boxSelect();
	void circleSelect();
	void freeformSelect();
	void setMaskColor(sf::Color color);

	int sign(int x)
	{
		return (x > 0) - (x < 0);
	}

	ButtonElement* boxSelectButton;
	ButtonElement* circleSelectButton;
	ButtonElement* freeformSelectButton;
	ButtonElement* allSelectButton;

	enum
	{
		BOX,
		CIRCLE,
		FREEFORM
	} selectMode;

	sf::Vector2i selectPos1;
	sf::Vector2i selectPos2;
	std::vector<sf::Vector2i> selectPosFreeForm;

	bool isSelecting = false;

	sf::Vector2i cursorPos;

	Layer* layer;
};
