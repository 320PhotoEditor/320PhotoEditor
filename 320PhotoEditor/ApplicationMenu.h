#pragma once

#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"
#include "GUI/ColorPickerElement.h"
#include "Layer/LayerManager.h"1

#include <fstream>

class ApplicationMenu
{
public:

	ApplicationMenu(sf::RenderWindow* renderWindow, LayerManager* toolManager);
	~ApplicationMenu();

	void update();

	sf::Color getForegroundColor();
	sf::Color getBackgroundColor();

	GUIContainer* getMenuContainer();
	GUIContainer* getColorContainer();

private:

	void buttonPressed(GUIElement* button, int status);

	LayerManager* layerManager;

	sf::RenderWindow* renderWindow;

	GUIContainer* menuContainer;
	GUIContainer* colorContainer;
	ButtonElement* fileMenuButton;
	ButtonElement* incrLightness;
	ButtonElement* decrLightness;
	ColorPickerElement* colorPicker;

};

