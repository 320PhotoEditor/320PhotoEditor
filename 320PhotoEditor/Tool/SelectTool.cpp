#include "SelectTool.h"

SelectTool::SelectTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	selectMode = BOX;
}

void SelectTool::init()
{
	sf::Texture* upTexture = new sf::Texture();
	upTexture->loadFromFile("../assets/button_up.png");
	sf::Texture* downTexture = new sf::Texture();
	downTexture->loadFromFile("../assets/button_down.png");
	sf::Texture* overTexture = new sf::Texture();
	overTexture->loadFromFile("../assets/button_over.png");

	boxSelectButton = new ButtonElement(upTexture, downTexture, overTexture);
	boxSelectButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(boxSelectButton);
	boxSelectButton->setSize({ .25, .25 });
	boxSelectButton->setPosition({ 0, 0 });

	circleSelectButton = new ButtonElement(upTexture, downTexture, overTexture);
	circleSelectButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(circleSelectButton);
	circleSelectButton->setSize({ .25, .25 });
	circleSelectButton->setPosition({ 0.25, 0 });

	freeformSelectButton = new ButtonElement(upTexture, downTexture, overTexture);
	freeformSelectButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(freeformSelectButton);
	freeformSelectButton->setSize({ .25, .25 });
	freeformSelectButton->setPosition({ 0.5, 0 });

	allSelectButton = new ButtonElement(upTexture, downTexture, overTexture);
	allSelectButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(allSelectButton);
	allSelectButton->setSize({ .25, .25 });
	allSelectButton->setPosition({ 0.75, 0 });
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

		switch (selectMode)
		{
		case BOX:
			boxSelect();
			break;
		case CIRCLE:
			circleSelect();
			break;
		case FREEFORM:
			freeformSelect();
			break;
		}

		isSelecting = false;
	}
}

void SelectTool::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
}

void SelectTool::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}

	if (button == boxSelectButton)
	{
		selectMode = BOX;
	}
	else if (button == circleSelectButton)
	{
		selectMode = CIRCLE;
	}
	else if (button == freeformSelectButton)
	{
		selectMode = FREEFORM;
	}
	else if (button == allSelectButton)
	{
		setMaskColor(sf::Color::White);
	}
}

void SelectTool::boxSelect()
{
	//clear the mask
	setMaskColor(sf::Color::Black);

	sf::Image* mask = layer->getMask();

	//set the selection to white(selected)
	for (int x = selectPos1.x; x != selectPos2.x; x += sign(selectPos2.x - selectPos1.x))
	{
		for (int y = selectPos1.y; y != selectPos2.x; y += sign(selectPos2.y - selectPos1.y))
		{
			mask->setPixel(x, y, sf::Color::White);
		}
	}
}

void SelectTool::circleSelect()
{
	setMaskColor(sf::Color::Black);

	sf::Image* mask = layer->getMask();

	int radius = sqrt(pow(selectPos1.x - selectPos2.x, 2) + pow(selectPos1.y - selectPos2.y, 2));

	//loop through the bounding box of the circle and find the pixels that are withing the circle by distance
	for (int x = selectPos1.x - selectPos2.x; x != selectPos2.x; x += sign(selectPos2.x - selectPos1.x))
	{
		for (int y = selectPos1.y - selectPos2.y; y != selectPos2.x; y += sign(selectPos2.y - selectPos1.y))
		{
			int distance = sqrt(pow(selectPos1.x - x, 2) + pow(selectPos1.y - y, 2));
			if(distance <= radius)
				mask->setPixel(x, y, sf::Color::White);
		}
	}
}

void SelectTool::freeformSelect()
{
	setMaskColor(sf::Color::Black);
	//TODO: add freeform
}

void SelectTool::setMaskColor(sf::Color color)
{
	sf::Image* mask = layer->getMask();
	//fast way of setting all the pixels in the image
	//just casting away the const when getting the pixel pointer
	auto px = reinterpret_cast<sf::Color*>(const_cast<sf::Uint8*>(mask->getPixelsPtr()));
	//fill the entire image with the color
	std::fill(px, px + mask->getSize().x * mask->getSize().y, color);
}
