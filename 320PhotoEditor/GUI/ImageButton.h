/*#pragma once

#include "../Tool/Tool.h"
#include "../Tool/ToolManager.h"
#include "../Layer/LayerManager.h"
#include "../InputListener.h"
#include "ButtonElement.h"

class ImageButton
{
public:
	ImageButton(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	//void keyPressed(sf::Keyboard::Key key);

	void buttonPressed(GUIElement* button, int status);
	void addInputListener(InputListener* listener);
private:


	ButtonElement* selectButton;
	ButtonElement* imageButton;
	Layer* layer;
	sf::RenderWindow* newWindow;
	std::set<InputListener*> inputListeners;
};*/
