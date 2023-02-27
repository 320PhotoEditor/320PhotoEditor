#include "PaintTool.h"

PaintTool::PaintTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	paintColor = sf::Color::Black;
	lastCursorPos = { 0, 0 };
	paintSize = 1;
}

void PaintTool::init()
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

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
		paintSize = std::min(++paintSize, 25);
		std::cout << paintSize << std::endl;
	}
	else if (button == decrSizeButton)
	{
		paintSize = std::max(--paintSize, 1);
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
				//TODO: this slows down alot when painting with the radius being large, maybe time to implement compute shaders or use some other method of finding what pixel is in the circle
				//or multhithread might work
				
				//loop through the bounding box of the circle and find the pixels that are withing the circle by distance
				for (int x = pos.x - paintSize; x != pos.x + paintSize; x++)
				{
					for (int y = pos.y - paintSize; y != pos.y + paintSize; y++)
					{
						int distance = sqrt(pow(pos.x - x, 2) + pow(pos.y - y, 2));
						if (distance <= paintSize)
							layer->getImage()->setPixel(x, y, paintColor);
					}
				}
			}
		}

		layer->reload();
	}
}
