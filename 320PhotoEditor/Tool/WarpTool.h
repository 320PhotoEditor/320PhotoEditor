#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "../ComputeShader.h"

class WarpTool : public Tool
{
public:

	WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void init();
	void start(Layer* layer);
	void stop() {};
	void run() {};
	
	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	//returns the indexes for the control point over the cursor
	//-1, -1 being no control point selected
	sf::Vector2i selectControlPoint(sf::Vector2i cursorPos);

	int* calculateTransformMatrx(std::vector<std::vector<sf::Vector2i>> controlPoints);

	void initControlPoints();

	void buttonPressed(GUIElement* button, int status);

private:

	bool down = false;
	sf::Vector2i cursorPos;
	sf::Vector2i selectedPoint;

	const int defaultSize = 5;

	std::vector<std::vector<sf::Vector2i>> controlPoints;

	Layer* layer;

	//stores a copy of the layer to sample from
	sf::Texture layerCopy;

	ButtonElement* increaseControlPointsX;
	ButtonElement* decreaseControlPointsX;
	ButtonElement* increaseControlPointsY;
	ButtonElement* decreaseControlPointsY;
	ButtonElement* startWarp;

	ComputeShader* warpCompute;
	unsigned int pointsBuf;
};
