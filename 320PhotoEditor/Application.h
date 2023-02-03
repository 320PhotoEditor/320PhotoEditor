#pragma once

#include "Common.h"
#include "InputListener.h"
#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"
#include "Tool/TestTool.h"
#include "Tool/ToolManager.h"
#include "Layer/LayerManager.h"

class Application
{
public:
	Application();
	~Application();

	//creates an SFML window with a name
	bool init(std::string windowName);

	//starts
	void run();

	void addInputListener(InputListener* listener);
	void removeInputListener(InputListener* listener);

private:

	void updateInputListeners(sf::Event event);

	sf::RenderWindow* window;

	ToolManager* toolManager;
	LayerManager* layerManager;

	std::set<InputListener*> inputListeners;
};
