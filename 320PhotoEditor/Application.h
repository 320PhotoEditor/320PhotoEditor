#pragma once

#include "Common.h"
#include "InputListener.h"
#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"
#include "Tool/Tool.h"
#include "Tool/ToolManager.h"

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

	ToolManager* toolManager;

private:

	void updateInputListeners(sf::Event event);

	sf::RenderWindow* window;

	std::set<InputListener*> inputListeners;
};
