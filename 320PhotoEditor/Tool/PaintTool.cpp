#include "PaintTool.h"

PaintTool::PaintTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	paintColor = sf::Color::Black;
	lastCursorPos = { 0, 0 };
}

void PaintTool::init()
{
	sf::Texture* upTexture = new sf::Texture();
	upTexture->loadFromFile("../assets/button_up.png");
	sf::Texture* downTexture = new sf::Texture();
	downTexture->loadFromFile("../assets/button_down.png");
	sf::Texture* overTexture = new sf::Texture();
	overTexture->loadFromFile("../assets/button_over.png");

	incrSizeButton = new ButtonElement(upTexture, downTexture, overTexture);
	incrSizeButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(incrSizeButton);
	incrSizeButton->setSize({ .25, .25 });
	incrSizeButton->setPosition({ 0, 0 });

	decrSizeButton = new ButtonElement(upTexture, downTexture, overTexture);
	decrSizeButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(decrSizeButton);
	decrSizeButton->setSize({ .25, .25 });
	decrSizeButton->setPosition({ 0.25, 0 });
}

void PaintTool::start(Layer* layer)
{
	this->layer = layer;
}

void PaintTool::mousePressed(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		isPainting = true;
		lastCursorPos = cursorPos;
		paint();
	}
}

void PaintTool::mouseReleased(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
		isPainting = false;
}

void PaintTool::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
	paint();
	lastCursorPos = pos;
}

void PaintTool::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}

	if (button == incrSizeButton)
	{
		paintSize = std::min(paintSize+1, 25);
		std::cout << paintSize << std::endl;
	}
	else if (button == decrSizeButton)
	{
		paintSize = std::max(paintSize - 1, 1);
		std::cout << paintSize << std::endl;
	}
}

void PaintTool::paint()
{
	if (isPainting && layer->isCursorOver(cursorPos))
	{
		paintColor = applicationMenu->getForegroundColor();

		sf::Vector2i paintPos = layer->cursorToPixel(cursorPos);
		sf::Vector2i lastPaintPos = layer->isCursorOver(lastCursorPos) ? layer->cursorToPixel(lastCursorPos) : paintPos;

		for (float f = 0; f < 1; f += 0.1)
		{
			sf::Vector2i pos = lastPaintPos + (paintPos - lastPaintPos) * f;
			if (layer->getMask()->getPixel(pos.x, pos.y) == sf::Color::White)
			{
				layer->getImage()->setPixel(pos.x, pos.y, paintColor);
			}
		}

		layer->reload();
	}
}
