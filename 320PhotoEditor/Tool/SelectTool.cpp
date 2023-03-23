#include "SelectTool.h"

SelectTool::SelectTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	selectMode = BOX;

	selectCompute = new ComputeShader("../assets/select_compute.comp");
}

void SelectTool::init()
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

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

		select();

		layer->loadMaskFromTexture();

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
		ComputeShader::bindTexture(layer->getMaskTexture()->getNativeHandle(), 0);
		selectCompute->use();
		selectCompute->setInt("selectMode", 3);
		sf::Vector2u layerSize = layer->getImage()->getSize();

		selectCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
	}
}

void SelectTool::select()
{
	ComputeShader::bindTexture(layer->getMaskTexture()->getNativeHandle(), 0);
	selectCompute->use();
	selectCompute->setVec2("firstPos", (float)selectPos1.x, (float)selectPos1.y);
	selectCompute->setVec2("secondPos", (float)selectPos2.x, (float)selectPos2.y);
	selectCompute->setInt("selectMode", (int)selectMode);
	sf::Vector2u layerSize = layer->getImage()->getSize();

	selectCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
}