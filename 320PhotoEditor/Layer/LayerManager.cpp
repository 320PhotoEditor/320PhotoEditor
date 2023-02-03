#include "LayerManager.h"

LayerManager::LayerManager(sf::RenderWindow* renderWindow, sf::Vector2u projectImageSize)
{
	this->renderWindow = renderWindow;
	this->projectImageSize = projectImageSize;
	createLayer(sf::Color::White);
}

void LayerManager::createLayer(sf::Color color)
{
	selectedLayer = new Layer(projectImageSize, color);
	sf::Sprite* sprite = selectedLayer->getSprite();

	sf::Vector2u imageCenter = projectImageSize / 2;
	sf::Vector2u screenCenter = renderWindow->getSize() / 2;

	sf::Vector2f offset(screenCenter.x - imageCenter.x, screenCenter.y - imageCenter.y);

	sprite->setPosition(offset);

	layers.insert(selectedLayer);
}

void LayerManager::removeSelectedLayer()
{
	layers.erase(selectedLayer);
}

Layer* LayerManager::getSelectedLayer()
{
	return selectedLayer;
}

void LayerManager::update()
{
	for (Layer* l : layers)
	{
		renderWindow->draw(*l->getSprite());
	}
}
