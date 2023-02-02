#pragma once

#include "../Common.h"
#include "Tool.h"
#include "../GUI/GUIContainer.h"
#include "../GUI/ButtonElement.h"
#include "../GUI/PanelElement.h"
#include "../InputListener.h"
#include "../Layer/Layer.h"

#define PANEL_ROWS 4

class ToolManager : public InputListener
{
public:

	ToolManager(sf::RenderWindow* renderWindow);

	void addTool(Tool* tool);

	GUIContainer* getGUIContainer();

	void update();

	void setSelectedLayer(Layer* layer);

	~ToolManager();

private:

	void keyPressed(sf::Keyboard::Key key);
	void keyReleased(sf::Keyboard::Key key);
	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseScrolled(int delta);
	void mouseMoved(sf::Vector2i pos);

	void buttonPressed(GUIElement* button, int status);

	std::map<ButtonElement*, Tool*> tools;

	GUIContainer* toolSelector;

	Tool* currentTool;

	Layer* layer;

};

