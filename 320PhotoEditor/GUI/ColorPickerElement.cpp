#include "ColorPickerElement.h"

ColorPickerElement::ColorPickerElement()
{
	img = sf::Texture();
	img.loadFromFile("../assets/color_picker.png");
	sprite = new sf::Sprite(img);
	lightness = 0.5;

	setDrawable(sprite);
	setVisible(true);
}

void ColorPickerElement::mousePressed(sf::Mouse::Button button)
{
	dragging = isCursorOver(cursorPos);
	if (dragging)
	{
		calcColor();
	}
}

void ColorPickerElement::mouseReleased(sf::Mouse::Button button)
{
	dragging = false;
}

void ColorPickerElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;

	if (isCursorOver(pos) && dragging)
	{
		savedPos = pos;
		calcColor();
	}
}

void ColorPickerElement::setSize(sf::Vector2f size)
{
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f containerSize = container->getSize() * windowSize;

	sprite->setScale(size * containerSize / sprite->getTexture()->getSize());

	this->size = size;
}

void ColorPickerElement::setPosition(sf::Vector2f pos)
{
	sf::Vector2u windowSize = container->getRenderWindow()->getSize();

	float aspect = (float)windowSize.x / (float)windowSize.y;

	sf::Vector2f position = pos * container->getSize() + container->getPosition();
	position.x /= aspect;

	sprite->setPosition(position * windowSize);
	this->pos = pos;
}

sf::Color ColorPickerElement::getPickedColor()
{
	return pickedColor;
}

void ColorPickerElement::setPickedColor(sf::Color color)
{
	pickedColor = color;
}

void ColorPickerElement::setLightness(float lightness)
{
	this->lightness = lightness;
	calcColor();
}

float ColorPickerElement::getLightness()
{
	return lightness;
}

void ColorPickerElement::calcColor()
{
	sf::Vector2f scale = sprite->getScale() * sprite->getTexture()->getSize();
	sf::Vector2f pos = sprite->getPosition();

	sf::Vector2f onPos = savedPos - pos;

	pickedColor = hsl2rgb(onPos.x / scale.x, 1 - (onPos.y / scale.y), lightness);

	updateFunc(this, 0);
}
