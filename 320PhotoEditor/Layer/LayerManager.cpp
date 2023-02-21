#include "LayerManager.h"

LayerManager::LayerManager(sf::RenderWindow* renderWindow, sf::Vector2u projectImageSize)
{
	this->renderWindow = renderWindow;
	this->projectImageSize = projectImageSize;

	selectionContainer = new GUIContainer({0, 0.25 }, {.2, .75}, renderWindow, true);
}

void LayerManager::createLayer(sf::Color color)
{
	Layer* layer = new Layer(projectImageSize, color, renderWindow);
	
	ButtonElement* button = createLayerButton(layer->getImage());

	sf::Sprite* sprite = layer->getSprite();

	sf::Vector2u imageCenter = projectImageSize / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x - imageCenter.x, screenCenter.y - imageCenter.y);

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

	sf::Vector2u imageCenter = projectImageSize / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x - imageCenter.x, screenCenter.y - imageCenter.y);

	sprite->setPosition(offset);

	layers.push_back(std::make_pair(layer, button));
	selectedLayer = layers.size() - 1;
}

void LayerManager::removeSelectedLayer()
{
	selectionContainer->removeElement(layers.at(selectedLayer).second);
	delete layers.at(selectedLayer).second;
	layers.erase(layers.begin() + selectedLayer);
	delete layers.at(selectedLayer).first;
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
	button->setPosition({ 0,0 });
	button->setSize({ 0.3, 0.075 });

	return button;
}
