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

	//returns the index for the control point over the cursor
	//-1 being no control point selected
	int selectControlPoint(sf::Vector2i cursorPos);

	void calculateTransformMatrx(sf::Vector2i originalControlPoints[4], sf::Vector2i controlPoints[4], Matrix3x3& transform);

	void initControlPoints();

	void buttonPressed(GUIElement* button, int status);

private:

	bool down = false;
	sf::Vector2i cursorPos;
	int selectedPoint;

	sf::Vector2i originalControlPoints[4];
	sf::Vector2i controlPoints[4];

	Layer* layer;

	//stores a copy of the layer to sample from
	sf::Texture layerCopy;
	ButtonElement* startWarp;

	ComputeShader* warpCompute;
	unsigned int pointsBuf;
};
