#include "PanelElement.h"

PanelElement::PanelElement(sf::Texture* texture)
{
	sprite = new sf::Sprite(*texture);

	setDrawable(sprite);
	setVisible(true);
}

void PanelElement::setSize(sf::Vector2f size)
{
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f containerSize = container->getSize() * windowSize;

	sprite->setScale(size * containerSize / sprite->getTexture()->getSize());

	this->size = size;
}

void PanelElement::setPosition(sf::Vector2f pos)
{
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f containerSize = container->getSize() * windowSize;
	sf::Vector2f position = pos + container->getPosition();

	sprite->setPosition(containerSize * position);
	this->pos = pos;
}
