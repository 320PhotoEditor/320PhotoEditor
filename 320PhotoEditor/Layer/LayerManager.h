#pragma once

#include "../Common.h"
#include "../GUI/GUIContainer.h"
#include "Layer.h"
#include "../GUI/ButtonElement.h"
#include "../AssetManager.h"

class ToolManager;

//handles layer selection gui
class LayerManager : public InputListener
{
public:
	LayerManager(sf::RenderWindow* renderWindow, ToolManager* toolManager, sf::Vector2u defaultImageSize);

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
	ButtonElement* createVisButton();

	void buttonPressed(GUIElement* button, int status);

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	sf::RenderWindow* renderWindow;
	ToolManager* toolManager;

	sf::Vector2u defaultImageSize;

	//layer, visiblity then its select button and visiblity button
	typedef std::tuple<Layer*, bool, ButtonElement*, ButtonElement*> LayerData;

	std::vector<LayerData> layers;

	unsigned int selectedLayer;

	GUIContainer* selectionContainer;
};
