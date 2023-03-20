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
	void stop() {};
	void run() { test->use(); sf::Texture::bind(layer->getSprite()->getTexture()); test->compute(800, 600, 1); };

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	void buttonPressed(GUIElement* button, int status);

private:

	void paint();

	sf::Texture* up;

	ButtonElement* incrSizeButton;
	ButtonElement* decrSizeButton;

	bool isPainting = false;

	sf::Color paintColor;

	int paintSize;

	sf::Vector2i cursorPos;
	sf::Vector2i lastCursorPos;

	Layer* layer;

	ComputeShader* test;
};

