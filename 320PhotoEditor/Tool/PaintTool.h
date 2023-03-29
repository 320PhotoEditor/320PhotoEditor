#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "../AssetManager.h"
#include "../ComputeShader.h"

class PaintTool : public Tool
{
public:

	PaintTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop();
	void run() {};

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);
	void mouseScrolled(int delta);
	void keyPressed(sf::Keyboard::Key key);
	void keyReleased(sf::Keyboard::Key key);

	void buttonPressed(GUIElement* button, int status);

private:

	void paint();

	bool scrollZoom = false;

	sf::Texture* up;

	ButtonElement* incrSizeButton;
	ButtonElement* decrSizeButton;

	bool isPainting = false;

	sf::Color paintColor;

	int paintSize;

	sf::Vector2i cursorPos;
	sf::Vector2i lastCursorPos;

	Layer* layer;

	ComputeShader* paintCompute;
};

