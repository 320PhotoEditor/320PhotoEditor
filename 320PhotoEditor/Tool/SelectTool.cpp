#include "SelectTool.h"

SelectTool::SelectTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void SelectTool::init()
{
}

void SelectTool::start(Layer* layer)
{
	this->layer = layer;
}

void SelectTool::mousePressed(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left && layer->isCursorOver(cursorPos))
	{
		selectPos1 = layer->cursorToPixel(cursorPos);
		isSelecting = true;
	}
}

void SelectTool::mouseReleased(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left && isSelecting)
	{
		selectPos2 = layer->cursorToPixel(cursorPos);

		sf::Image* mask = layer->getMask();

		//fast way of setting all the pixels in the image
		//just casting away the const when getting the pixel pointer
		auto px = reinterpret_cast<sf::Color*>(const_cast<sf::Uint8*>(mask->getPixelsPtr()));
		std::fill(px, px + mask->getSize().x * mask->getSize().y, sf::Color::Black);

		for (int x = selectPos1.x; x != selectPos2.x; x += sign(selectPos2.x - selectPos1.x))
		{
			for (int y = selectPos1.y; y != selectPos2.x; y += sign(selectPos2.y - selectPos1.y))
			{
				mask->setPixel(x, y, sf::Color::White);
			}
		}

		isSelecting = false;
	}
}

void SelectTool::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
}
