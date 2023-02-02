#pragma once

#include "Tool.h"

class TestTool : public Tool
{
public:
	TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void start(Layer* layer) { std::cout << "started tool\n"; };
	void stop() {};
	void run() {};

	void keyPressed(sf::Keyboard::Key key) { std::cout << "tool activated\n"; };
};

