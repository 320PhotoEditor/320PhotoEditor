#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"

class TestTool : public Tool
{
public:
	TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};

	void keyPressed(sf::Keyboard::Key key);
//<<<<<<< HEAD
//    void mousePressed(sf::Mouse::Button button);
//=======

	void buttonPressed(GUIElement* button, int status) { }
//>>>>>>> main
private:

	Layer* layer;
};

