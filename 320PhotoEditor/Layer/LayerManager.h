#pragma once

#include "../Common.h"
#include "../GUI/GUIContainer.h"
#include "Layer.h"

//handles layer selection gui
class LayerManager
{
public:
	LayerManager(sf::RenderWindow* renderWindow, sf::Vector2u projectImageSize);

	//creates a new layer and then selects it
	void createLayer(sf::Color color);
	//removes the selected layer
	void removeSelectedLayer();

	Layer* getSelectedLayer();

	//draws layer selection and image on screen
	void update();

private:

	sf::RenderWindow* renderWindow;

	sf::Vector2u projectImageSize;

	std::set<Layer*> layers;

	Layer* selectedLayer;
};
