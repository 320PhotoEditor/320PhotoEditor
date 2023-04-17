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

	//scale it so its always the same size on screen regardless of resolution
	float scale = 0.7 * renderWindow->getSize().x / sprite->getTexture()->getSize().x;
	sprite->setScale(scale, scale);

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
	sf::Vector2f pos = sprite->getPosition();
	sf::Vector2f origin = sprite->getOrigin();
	sf::Vector2f scale = sprite->getScale();
	sf::Vector2u size = sprite->getTexture()->getSize();

	sf::Vector2f dx = cursorPos - pos;

	sf::Vector2i pixel =  sf::Vector2i(dx.x / scale.x + origin.x, dx.y / scale.y + origin.y);
	return pixel;
}

bool Layer::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2u windowSize = renderWindow->getSize();
	sf::Vector2f spritePos = sprite->getPosition();

	float left = spritePos.x - sprite->getOrigin().x;
	float right = spritePos.x + sprite->getTexture()->getSize().x - sprite->getOrigin().x;
	float top = spritePos.y - sprite->getOrigin().y;
	float bottom = spritePos.y + sprite->getTexture()->getSize().y - sprite->getOrigin().y;

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