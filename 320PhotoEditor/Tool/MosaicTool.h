#pragma once

#include "Tool.h"
#include "ToolManager.h"
//#include "../Layer/LayerManager.h"
#include "../InputListener.h"
#include "../GUI/ButtonElement.h"
#include "../GUI/ImageButton.h"

class MosaicTool : public Tool
{
public:
	MosaicTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	//void keyPressed(sf::Keyboard::Key key);

	void buttonPressed(GUIElement* button, int status);
	void addInputListener(InputListener* listener);
private:

	ToolManager* toolManager;
	//LayerManager* layerManager;
	ButtonElement* selectButton;
	//ButtonElement* imageButton;
	Layer* layer;
	sf::RenderWindow* newWindow;
	std::set<InputListener*> inputListeners;
};

