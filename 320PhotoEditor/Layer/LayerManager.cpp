#include "LayerManager.h"
#include "../Tool/ToolManager.h"

LayerManager::LayerManager(sf::RenderWindow* renderWindow, ToolManager* toolManager, sf::Vector2u defaultImageSize)
{
	this->renderWindow = renderWindow;
	this->toolManager = toolManager;
	this->defaultImageSize = defaultImageSize;

	selectionContainer = new GUIContainer({0, 0.25 }, {.2, .75}, renderWindow, true);
}

void LayerManager::createLayer(sf::Color color)
{
	Layer* layer = new Layer(defaultImageSize, color, renderWindow);
	
	ButtonElement* button = createLayerButton(const_cast<sf::Texture*>(layer->getSprite()->getTexture()));
	ButtonElement* visButton = createVisButton();

	sf::Sprite* sprite = layer->getSprite();

	sf::Vector2u imageCenter = defaultImageSize / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x, screenCenter.y);

	sprite->setOrigin({ (float)imageCenter.x, (float)imageCenter.y });
	sprite->setPosition(offset);

	layers.push_back(std::make_tuple(layer, true, button, visButton));
	selectedLayer = layers.size() - 1;
}

void LayerManager::createLayerFromFile(std::string filePath)
{
	Layer* layer = new Layer(filePath, renderWindow);

	if (layer->getImage() == nullptr)
	{
		delete layer;
		return;
	}

	ButtonElement* button = createLayerButton(const_cast<sf::Texture*>(layer->getSprite()->getTexture()));
	ButtonElement* visButton = createVisButton();

	sf::Sprite* sprite = layer->getSprite();

	sf::Vector2u imageCenter = layer->getImage()->getSize() / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x, screenCenter.y);

	sprite->setOrigin({ (float)imageCenter.x, (float)imageCenter.y });
	sprite->setPosition(offset);

	layers.push_back(std::make_tuple(layer, true, button, visButton));
	selectedLayer = layers.size() - 1;
}

void LayerManager::removeSelectedLayer()
{
	selectionContainer->removeElement(std::get<2>(layers.at(selectedLayer)));
	delete std::get<2>(layers.at(selectedLayer));
	selectionContainer->removeElement(std::get<3>(layers.at(selectedLayer)));
	delete std::get<3>(layers.at(selectedLayer));
	delete std::get<0>(layers.at(selectedLayer));
	layers.erase(layers.begin() + selectedLayer);
	selectedLayer--;
}

Layer* LayerManager::getSelectedLayer()
{
	return std::get<0>(layers.at(selectedLayer));
}

void LayerManager::update()
{
	selectionContainer->render();

	for (LayerData l : layers)
	{
		if (std::get<1>(l))
		{
			renderWindow->draw(*std::get<0>(l)->getSprite());
		}
	}
}

ButtonElement* LayerManager::createLayerButton(sf::Texture* tex)
{
	ButtonElement* button = new ButtonElement(tex, tex, tex);
	selectionContainer->addElement(button);
	button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	button->setPosition({ 0, 1 - (layers.size() * 0.08f) - 0.1f });
	button->setSize({ 0.3, 0.075 });

	return button;
}

ButtonElement* LayerManager::createVisButton()
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");

	ButtonElement* button = new ButtonElement(upTexture, downTexture, nullptr, true);
	selectionContainer->addElement(button);
	button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	button->setPosition({ 0.35, 1 - (layers.size() * 0.08f) - 0.1f });
	button->setSize({ 0.3, 0.075 });

	return button;
}

void LayerManager::buttonPressed(GUIElement* button, int status)
{
	int i = 0;
	for (LayerData layer : layers)
	{
		if (std::get<2>(layer) == button && status != ButtonElement::ButtonState::DOWN)
		{
			selectedLayer = i;
			toolManager->setSelectedLayer(getSelectedLayer());
			toolManager->restartTool();
			break;
		}
		else if (std::get<3>(layer) == button)
		{
			std::get<1>(layers.at(i)) = (status == ButtonElement::ButtonState::UP);
			break;
		}
		i++;
	}
}

void LayerManager::mousePressed(sf::Mouse::Button button)
{
	selectionContainer->mousePressed(button);
}

void LayerManager::mouseReleased(sf::Mouse::Button button)
{
	selectionContainer->mouseReleased(button);
}

void LayerManager::mouseMoved(sf::Vector2i pos)
{
	selectionContainer->mouseMoved(pos);
}
