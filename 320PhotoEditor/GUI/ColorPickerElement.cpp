#include "ColorPickerElement.h"

ColorPickerElement::ColorPickerElement()
{
	img = sf::Texture();
	img.loadFromFile("../assets/color_picker.png");
	sprite = new sf::Sprite(img);

	setDrawable(sprite);
	setVisible(true);
}

void ColorPickerElement::mousePressed(sf::Mouse::Button button)
{
	dragging = isCursorOver(cursorPos);
}

void ColorPickerElement::mouseReleased(sf::Mouse::Button button)
{
	dragging = false;
}

void ColorPickerElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
}

void ColorPickerElement::setSize(sf::Vector2f size)
{
	if (size.x != size.y)
	{
		std::cerr << "Error: Color picker size must be square\n";
		size.y = size.x;
	}

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
