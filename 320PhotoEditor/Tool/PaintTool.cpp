#include "PaintTool.h"

PaintTool::PaintTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	paintColor = sf::Color::Black;
}

void PaintTool::start(Layer* layer)
{
	this->layer = layer;

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

void PaintTool::mousePressed(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		isPainting = true;
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
}

void PaintTool::buttonPressed(GUIElement* button, int status)
{
	if (button == color1Button && status == ButtonElement::ButtonState::DOWN)
	{
		paintColor = sf::Color::Black;
	}
	if (button == color2Button && status == ButtonElement::ButtonState::DOWN)
	{
		paintColor = sf::Color::White;
	}
	if (button == color3Button && status == ButtonElement::ButtonState::DOWN)
	{
		paintColor = sf::Color::Blue;
	}
}

void PaintTool::paint()
{
	if (isPainting && layer->isCursorOver(cursorPos))
	{
		sf::Vector2i pixelPos = layer->cursorToPixel(cursorPos);
		layer->getImage()->setPixel(pixelPos.x, pixelPos.y, paintColor);
		layer->reload();
	}
}
