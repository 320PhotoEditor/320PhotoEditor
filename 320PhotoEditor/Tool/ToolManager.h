#pragma once

#include "../Common.h"
#include "Tool.h"
#include "../GUI/GUIContainer.h"
#include "../GUI/ButtonElement.h"
#include "../GUI/PanelElement.h"

#define PANEL_ROWS 4

class ToolManager
{
public:

	ToolManager(sf::RenderWindow* renderWindow);

	void addTool(Tool* tool);

	GUIContainer* getGUIContainer();

	void update();

	~ToolManager();

private:

	void buttonPressed(GUIElement* button, int status);

	std::map<ButtonElement*, Tool*> tools;

	PanelElement* background;

	GUIContainer* toolSelector;

	Tool* currentTool;

};

