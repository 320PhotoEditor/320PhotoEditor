#include "LayerManager.h"

LayerManager::LayerManager(sf::RenderWindow* window, sf::Vector2u projectImageSize)
{
	this->projectImageSize = projectImageSize;
	createLayer(sf::Color::White);
}

void LayerManager::createLayer(sf::Color color)
{
	selectedLayer = new Layer(projectImageSize, color);
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
