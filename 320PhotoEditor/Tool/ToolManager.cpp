#include "ToolManager.h"

ToolManager::ToolManager(sf::RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
	toolSelector = new GUIContainer({0, 0.025}, {.2, .3}, renderWindow);
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

	//create a tool config container for the tool
	tool->setContainer(new GUIContainer({ 0, 0.025 }, { .2, .2 }, renderWindow, true));
	tool->setMenu(applicationMenu);
	tool->init();

	tools.emplace(std::make_pair(button, tool));
}

GUIContainer* ToolManager::getGUIContainer()
{
	return toolSelector;
}

void ToolManager::update()
{
	toolSelector->render();

	if (currentTool)
	{
		currentTool->run();
		currentTool->getContainer()->render();
	}
}

void ToolManager::setSelectedLayer(Layer* layer)
{
	this->layer = layer;
}

void ToolManager::restartTool()
{
	if (currentTool)
	{
		currentTool->stop();
		currentTool->start(layer);
	}
}

void ToolManager::setApplicationMenu(ApplicationMenu* applicationMenu)
{
	this->applicationMenu = applicationMenu;
}

ToolManager::~ToolManager()
{
	//cleanup buttons
	for (auto tool : tools)
	{
		delete tool.second->getContainer(); //cleanup the tool guicontainers that were created
		delete tool.first;
	}

	delete toolSelector;
}

void ToolManager::keyPressed(sf::Keyboard::Key key)
{
	if (currentTool)
	{
		currentTool->keyPressed(key);
	}
}

void ToolManager::keyReleased(sf::Keyboard::Key key)
{
	if (currentTool)
	{
		currentTool->keyReleased(key);
	}
}

void ToolManager::mousePressed(sf::Mouse::Button button)
{
	if (currentTool)
	{
		currentTool->mousePressed(button);
		currentTool->getContainer()->mousePressed(button);
	}

	toolSelector->mousePressed(button);
}

void ToolManager::mouseReleased(sf::Mouse::Button button)
{
	if (currentTool)
	{
		currentTool->mouseReleased(button);
		currentTool->getContainer()->mouseReleased(button);
	}

	toolSelector->mouseReleased(button);
}

void ToolManager::mouseScrolled(int delta)
{
	if (currentTool)
	{
		currentTool->mouseScrolled(delta);
	}
}

void ToolManager::mouseMoved(sf::Vector2i pos)
{
	if (currentTool)
	{
		currentTool->mouseMoved(pos);
		currentTool->getContainer()->mouseMoved(pos);
	}

	toolSelector->mouseMoved(pos);
}

void ToolManager::windowResize()
{
	toolSelector->windowResize();
}

void ToolManager::buttonPressed(GUIElement* button, int status)
{
	if (status == ButtonElement::DOWN)
	{
		if (currentTool)
		{
			currentTool->stop();
		}
		currentTool = tools.at((ButtonElement*)button);
		currentTool->start(layer);
	}
}
