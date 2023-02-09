#include "Layer.h"

Layer::Layer(sf::Vector2u size, sf::Color color, sf::RenderWindow* renderWindow)
{
	image = new sf::Image();
	image->create(size.x, size.y, color);

	mask = new sf::Image();
	mask->create(size.x, size.y, sf::Color::White);

	texture = sf::Texture();
	texture.loadFromImage(*image);

	sprite = new sf::Sprite(texture);

	visible = true;

	this->renderWindow = renderWindow;
}

sf::Image* Layer::getImage()
{
	return image;
}

sf::Image* Layer::getMask()
{
	return mask;
}

sf::Sprite* Layer::getSprite()
{
	return sprite;
}

sf::Vector2i Layer::cursorToPixel(sf::Vector2i cursorPos)
{
	//TODO: make adjust for image scale and position
	return sf::Vector2i(cursorPos.x - sprite->getPosition().x, cursorPos.y - sprite->getPosition().y);
}

bool Layer::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2u windowSize = renderWindow->getSize();
	sf::Vector2f spritePos = sprite->getPosition();

	float left = spritePos.x;
	float right = spritePos.x + sprite->getTexture()->getSize().x;
	float top = spritePos.y;
	//TODO: last pixel on y axis doesnt want to be written to for some reason
	float bottom = spritePos.y + sprite->getTexture()->getSize().y - 1;

	return cursorPos.x >= left && cursorPos.x <= right && cursorPos.y >= top && cursorPos.y <= bottom;
}

void Layer::reload()
{
	texture.loadFromImage(*image);
}

Layer::~Layer()
{
	delete sprite;
	delete image;
}