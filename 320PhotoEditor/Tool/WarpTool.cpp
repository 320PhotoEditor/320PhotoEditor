#include "WarpTool.h"

WarpTool::WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void WarpTool::init()
{
}

void WarpTool::start(Layer* layer)
{
	this->layer = layer;
}

//TODO:
sf::Vector2i WarpTool::selectControlPoint(sf::Vector2i cursorPos)
{
	return sf::Vector2i(-1, -1);
}
