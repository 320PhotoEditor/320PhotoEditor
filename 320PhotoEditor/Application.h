#pragma once

#include "Common.h"
#include "InputListener.h"
#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"

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

	GUIContainer* guiContainer;

	ButtonElement* button;

private:

	void updateInputListeners(sf::Event event);

	sf::RenderWindow* window;

	std::set<InputListener*> inputListeners;
};
