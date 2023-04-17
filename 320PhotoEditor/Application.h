#pragma once

#include "Common.h"
#include "InputListener.h"
#include "WindowListener.h"
#include "GUI/GUIContainer.h"
#include "GUI/ButtonElement.h"
#include "Tool/TestTool.h"
#include "Tool/PaintTool.h"
#include "Tool/SelectTool.h"
#include "Tool/MosaicTool.h"
#include "Tool/ToolManager.h"
#include "Tool/FilterTool.h"
#include "Tool/WarpTool.h"
#include "Tool/Zoom.h"
#include "Tool/HistogramTool.h"
#include "Tool/EditTool.h"
#include "Layer/LayerManager.h"
#include "ApplicationMenu.h"
#include "AssetManager.h"
#include "ComputeShader.h"

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

	void addWindowListener(WindowListener* listener);
	void removeWindowListener(WindowListener* listener);

private:

	void updateInputListeners(sf::Event event);
	void updateWindowListeners(sf::Event event);

	sf::RenderWindow* window;

	ToolManager* toolManager;
	LayerManager* layerManager;
	ApplicationMenu* applicationMenu;

	std::set<InputListener*> inputListeners;
	std::set<WindowListener*> windowListeners;
};
