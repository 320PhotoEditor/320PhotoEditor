#pragma once

#include "../Common.h"
#include "../GUI/GUIContainer.h"
#include "Layer.h"

//handles layer selection gui
class LayerManager
{
public:
	LayerManager(sf::Vector2u projectImageSize);

	//creates a new layer and then selects it
	void createLayer(sf::Color color);

	//removes the selected layer
	void removeSelectedLayer();



private:

	sf::Vector2u projectImageSize;

	std::set<Layer*> layers;

	Layer* selectedLayer;
};

