#include "ToolManager.h"

ToolManager::ToolManager(sf::RenderWindow* renderWindow)
{
	toolSelector = new GUIContainer({0,0}, {.2, .3}, renderWindow);
	toolSelector->setVisible(true);
	currentTool = nullptr;
}

void ToolManager::addTool(Tool* tool)
{
	ButtonElement* button = new ButtonElement(tool->up, tool->down, tool->over);


	button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });

	toolSelector->addElement(button);

	button->setSize({1.0 / PANEL_ROWS, 1.0 / PANEL_ROWS * 0.666});

	//fit the buttons side by side and place them vertically when running out of horizontal room
	button->setPosition(sf::Vector2f(((int)tools.size() % PANEL_ROWS) * (1.0 / PANEL_ROWS), (int)(tools.size() / PANEL_ROWS) * (1.0 / PANEL_ROWS) * 0.666));

	tools.emplace(std::make_pair(button, tool));
}

GUIContainer* ToolManager::getGUIContainer()
{
	return toolSelector;
}

void ToolManager::update()
{
	toolSelector->render();
}

ToolManager::~ToolManager()
{
	//cleanup buttons
	for (auto tool : tools)
	{
		tool.second;
	}

	delete toolSelector;
}

void ToolManager::buttonPressed(GUIElement* button, int status)
{
	if (status == ButtonElement::DOWN)
	{
		currentTool->stop();
		currentTool = tools.at((ButtonElement*)button);
		currentTool->start();
	}
}
