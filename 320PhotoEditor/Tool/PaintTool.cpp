#include "PaintTool.h"

PaintTool::PaintTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	this->up = up;
	paintCompute = new ComputeShader("../assets/paint_compute.comp");
	
	paintColor = sf::Color::Black;
	lastCursorPos = { 0, 0 };
	paintSize = 5;
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

void PaintTool::stop()
{
	layer->loadImageFromTexture();
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
		paintSize = std::min(++paintSize, 1000);
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
	if (isPainting)
	{
		//TODO: make compute shader respect the layer mask
		paintColor = applicationMenu->getForegroundColor();

		ComputeShader::bindTexture(layer->getSprite()->getTexture()->getNativeHandle());
		paintCompute->use();
		sf::Vector2i paintPos = layer->cursorToPixel(cursorPos);
		sf::Vector2i lastpaintPos = layer->cursorToPixel(lastCursorPos);
		paintCompute->setVec2("firstPos", (float)paintPos.x, (float)paintPos.y);
		paintCompute->setVec2("secondPos", (float)lastpaintPos.x, (float)lastpaintPos.y);

		paintCompute->setFloat("paintSize", paintSize);
		paintCompute->setVec3("color", paintColor.r / 255.0f, paintColor.g / 255.0f, paintColor.b / 255.0f);

		sf::Vector2u layerSize = layer->getImage()->getSize();

		paintCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
	}
}
