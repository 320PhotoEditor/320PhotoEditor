#pragma once

#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"
#include "GUI/ColorPickerElement.h"
#include "Layer/LayerManager.h"
#include "AssetManager.h"

#include <fstream>

class ToolManager;

class ApplicationMenu
{
public:

	ApplicationMenu(sf::RenderWindow* renderWindow, LayerManager* layerManager, ToolManager* toolManager);
	~ApplicationMenu();

	void update();

	sf::Color getForegroundColor();
	sf::Color getBackgroundColor();

	GUIContainer* getMenuContainer();
	GUIContainer* getColorContainer();

private:

	void buttonPressed(GUIElement* button, int status);

	LayerManager* layerManager;
	ToolManager* toolManager;

	sf::RenderWindow* renderWindow;

	GUIContainer* menuContainer;
	GUIContainer* colorContainer;
	ButtonElement* fileMenuButton;
	ButtonElement* newBlankButton;
	ButtonElement* newTransparentButton;
	ButtonElement* incrLightness;
	ButtonElement* decrLightness;
	ButtonElement* incrTransparency;
	ButtonElement* decrTransparency;
	ButtonElement* foregroundColor;
	ButtonElement* backgroundColor;

	sf::Texture* foreColorTexture;
	sf::Texture* backColorTexture;

	sf::Color foreColor;
	sf::Color backColor;

	bool foreSelect = true;

	ColorPickerElement* colorPicker;

};

