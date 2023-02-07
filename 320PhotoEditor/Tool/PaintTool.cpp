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

	color1Button = new ButtonElement(upTexture, downTexture, overTexture);
	color1Button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(color1Button);
	color1Button->setSize({ .25, .25 });
	color1Button->setPosition({ 0, 0 });

	color2Button = new ButtonElement(upTexture, downTexture, overTexture);
	color2Button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(color2Button);
	color2Button->setSize({ .25, .25 });
	color2Button->setPosition({ 0.25, 0 });

	color3Button = new ButtonElement(upTexture, downTexture, overTexture);
	color3Button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(color3Button);
	color3Button->setSize({ .25, .25 });
	color3Button->setPosition({ 0.5, 0 });
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

	if (button == color1Button)
	{
		paintColor = sf::Color::Black;
	}
	if (button == color2Button)
	{
		paintColor = sf::Color::White;
	}
	if (button == color3Button)
	{
		paintColor = sf::Color::Blue;
	}
}

void PaintTool::paint()
{
	if (isPainting && layer->isCursorOver(cursorPos))
	{
		sf::Vector2i paintPos = layer->cursorToPixel(cursorPos);
		sf::Vector2i lastPaintPos = layer->isCursorOver(lastCursorPos) ? layer->cursorToPixel(lastCursorPos) : cursorPos;

		for (float f = 0; f < 1; f += 0.1)
		{
			sf::Vector2i pos = lastPaintPos + (paintPos - lastPaintPos) * f;
			layer->getImage()->setPixel(pos.x, pos.y, paintColor);
		}

		layer->reload();
	}
}
