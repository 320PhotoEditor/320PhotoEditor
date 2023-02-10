#pragma once

#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"
#include "Layer/LayerManager.h"1

#include <fstream>

class ApplicationMenu
{
public:

	ApplicationMenu(sf::RenderWindow* renderWindow, LayerManager* toolManager);
	~ApplicationMenu();

	void update();
	GUIContainer* getGUIContainer();

private:

	void buttonPressed(GUIElement* button, int status);

	LayerManager* layerManager;

	GUIContainer* menuContainer;
	ButtonElement* fileMenuButton;

};

