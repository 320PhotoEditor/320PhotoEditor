#include "LayerManager.h"

LayerManager::LayerManager(sf::RenderWindow* renderWindow, sf::Vector2u defaultImageSize)
{
	this->renderWindow = renderWindow;
	this->defaultImageSize = defaultImageSize;

	selectionContainer = new GUIContainer({0, 0.25 }, {.2, .75}, renderWindow, true);
}

void LayerManager::createLayer(sf::Color color)
{
	Layer* layer = new Layer(defaultImageSize, color, renderWindow);
	
	ButtonElement* button = createLayerButton(layer->getImage());

	sf::Sprite* sprite = layer->getSprite();

	sf::Vector2u imageCenter = defaultImageSize / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x, screenCenter.y);

	sprite->setOrigin({ (float)imageCenter.x, (float)imageCenter.y });
	sprite->setPosition(offset);

	layers.push_back(std::make_pair(layer, button));
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

	ButtonElement* button = createLayerButton(layer->getImage());

	sf::Sprite* sprite = layer->getSprite();

	sf::Vector2u imageCenter = layer->getImage()->getSize() / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x, screenCenter.y);

	sprite->setOrigin({ (float)imageCenter.x, (float)imageCenter.y });
	sprite->setPosition(offset);

	layers.push_back(std::make_pair(layer, button));
	selectedLayer = layers.size() - 1;
}

void LayerManager::removeSelectedLayer()
{
	selectionContainer->removeElement(layers.at(selectedLayer).second);
	delete layers.at(selectedLayer).second;
	delete layers.at(selectedLayer).first;
	layers.erase(layers.begin() + selectedLayer);
	selectedLayer--;
}

Layer* LayerManager::getSelectedLayer()
{
	return layers.at(selectedLayer).first;
}

void LayerManager::update()
{
	selectionContainer->render();

	for (auto l : layers)
	{
		renderWindow->draw(*l.first->getSprite());
	}
}

ButtonElement* LayerManager::createLayerButton(sf::Image* img)
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromImage(*img);
	ButtonElement* button = new ButtonElement(tex, tex, tex);
	selectionContainer->addElement(button);
	button->setPosition({ 0, 1 - (layers.size() * 0.08f) - 0.1f });
	button->setSize({ 0.3, 0.075 });

	return button;
}

void LayerManager::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}

	int i = 0;
	for (auto layer : layers)
	{
		if (layer.second == button)
		{
			selectedLayer = i;
		}
		i++;
	}
}
