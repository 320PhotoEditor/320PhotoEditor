#include "Layer.h"

Layer::Layer(sf::Vector2u size, sf::Color color, sf::RenderWindow* renderWindow)
{	
	sf::Image* image = new sf::Image();
	image->create(size.x, size.y, color);

	createLayer(image, renderWindow);
}

Layer::Layer(std::string filePath, sf::RenderWindow* renderWindow)
{
	sf::Image* image = new sf::Image();
	image->loadFromFile(filePath);

	createLayer(image, renderWindow);
}

void Layer::createLayer(sf::Image* image, sf::RenderWindow* renderWindow)
{
	this->image = image;

	mask = new sf::Image();
	mask->create(image->getSize().x, image->getSize().y, sf::Color::White);
	maskTexture.loadFromImage(*mask);

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

sf::Texture* Layer::getMaskTexture()
{
	return &maskTexture;
}

sf::Sprite* Layer::getSprite()
{
	return sprite;
}

sf::Vector2i Layer::cursorToPixel(sf::Vector2i cursorPos)
{
	//TODO: make adjust for image scale and position
	return sf::Vector2i(cursorPos.x - sprite->getPosition().x + sprite->getOrigin().x, cursorPos.y - sprite->getPosition().y + sprite->getOrigin().y);
}

bool Layer::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2u windowSize = renderWindow->getSize();
	sf::Vector2f spritePos = sprite->getPosition();

	float left = spritePos.x - sprite->getOrigin().x;
	float right = spritePos.x + sprite->getTexture()->getSize().x - sprite->getOrigin().x;
	float top = spritePos.y - sprite->getOrigin().y;
	//TODO: last pixel on y axis doesnt want to be written to for some reason
	float bottom = spritePos.y + sprite->getTexture()->getSize().y - sprite->getOrigin().y - 1;

	return cursorPos.x >= left && cursorPos.x <= right && cursorPos.y >= top && cursorPos.y <= bottom;
}

void Layer::reload()
{
	texture.loadFromImage(*image);
}

void Layer::reloadMask()
{
	maskTexture.loadFromImage(*mask);
}

void Layer::loadImageFromTexture()
{
	sf::Image img = texture.copyToImage();
	image->copy(img, 0, 0);
}

void Layer::loadMaskFromTexture()
{
	sf::Image img = maskTexture.copyToImage();
	mask->copy(img, 0, 0);
}

Layer::~Layer()
{
	delete sprite;
	delete image;
}