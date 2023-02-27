#pragma once

#include "../Common.h"
#include "../GUI/GUIContainer.h"
#include "Layer.h"
#include "../GUI/ButtonElement.h"

//handles layer selection gui
class LayerManager
{
public:
	LayerManager(sf::RenderWindow* renderWindow, sf::Vector2u defaultImageSize);

	//creates a new layer and then selects it
	void createLayer(sf::Color color);

	//also selects when successfully loaded
	void createLayerFromFile(std::string filePath);
	
	//removes the selected layer
	void removeSelectedLayer();

	Layer* getSelectedLayer();

	//draws layer selection and image on screen
	void update();

private:

	ButtonElement* createLayerButton(sf::Image* img);

	void buttonPressed(GUIElement* button, int status);

	sf::RenderWindow* renderWindow;

	sf::Vector2u defaultImageSize;

	std::vector<std::pair<Layer*, ButtonElement*>> layers;

	unsigned int selectedLayer;

	GUIContainer* selectionContainer;
};
