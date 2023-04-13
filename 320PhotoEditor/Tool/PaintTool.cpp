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
	sf::Texture* incrupTexture = AssetManager::getInstance().getTexture("../assets/incr_button_up.png");
	sf::Texture* incrdownTexture = AssetManager::getInstance().getTexture("../assets/incr_button_down.png");
	sf::Texture* incroverTexture = AssetManager::getInstance().getTexture("../assets/incr_button_over.png");
	sf::Texture* decrupTexture = AssetManager::getInstance().getTexture("../assets/decr_button_up.png");
	sf::Texture* decrdownTexture = AssetManager::getInstance().getTexture("../assets/decr_button_down.png");
	sf::Texture* decroverTexture = AssetManager::getInstance().getTexture("../assets/decr_button_over.png");

	incrSizeButton = new ButtonElement(incrupTexture, incrdownTexture, incroverTexture);
	incrSizeButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(incrSizeButton);
	incrSizeButton->setSize({ .25, .25 });
	incrSizeButton->setPosition({ 0.25, 0 });

	decrSizeButton = new ButtonElement(decrupTexture, decrdownTexture, decroverTexture);
	decrSizeButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(decrSizeButton);
	decrSizeButton->setSize({ .25, .25 });
	decrSizeButton->setPosition({ 0, 0 });
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

void PaintTool::mouseScrolled(int delta)
{
	if (scrollZoom)
	{
		paintSize = std::max(paintSize + delta, 1);
		std::cout << paintSize << std::endl;
	}
}

void PaintTool::keyPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::LAlt) scrollZoom = true;
}

void PaintTool::keyReleased(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::LAlt) scrollZoom = false;
}

void PaintTool::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}

	if (button == incrSizeButton)
	{
		++paintSize;
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
		paintColor = applicationMenu->getForegroundColor();

		ComputeShader::bindTexture(layer->getSprite()->getTexture()->getNativeHandle(), 0);
		ComputeShader::bindTexture(layer->getMaskTexture()->getNativeHandle(), 1);
		paintCompute->use();
		sf::Vector2i paintPos = layer->cursorToPixel(cursorPos);
		sf::Vector2i lastpaintPos = layer->cursorToPixel(lastCursorPos);
		paintCompute->setVec2("firstPos", (float)paintPos.x, (float)paintPos.y);
		paintCompute->setVec2("secondPos", (float)lastpaintPos.x, (float)lastpaintPos.y);

		paintCompute->setFloat("paintSize", paintSize);
		paintCompute->setVec4("color", paintColor.r / 255.0f, paintColor.g / 255.0f, paintColor.b / 255.0f, paintColor.a / 255.0f);

		sf::Vector2u layerSize = layer->getImage()->getSize();

		paintCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
	}
}
