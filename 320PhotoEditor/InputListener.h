#pragma once
#include "Common.h"

class InputListener
{
public:
	virtual void keyPressed(sf::Keyboard::Key key) {};
	virtual void keyReleased(sf::Keyboard::Key key) {};
	virtual void mousePressed(sf::Mouse::Button button) {};
	virtual void mouseReleased(sf::Mouse::Button button) {};
	virtual void mouseScrolled(int delta) {};
	virtual void mouseMoved(sf::Vector2i pos) {};

	//internal, do not use
	void setWindow(sf::Window* window);
	
private:
	sf::Window* window;
};
