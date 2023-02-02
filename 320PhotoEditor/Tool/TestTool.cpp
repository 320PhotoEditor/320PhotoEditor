#include "TestTool.h"

TestTool::TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void TestTool::start(Layer* layer)
{
	this->layer = layer;
}

void TestTool::keyPressed(sf::Keyboard::Key key)
{
	layer->getImage()->setPixel(0, 0, sf::Color::Red); 
	layer->reload();
}
