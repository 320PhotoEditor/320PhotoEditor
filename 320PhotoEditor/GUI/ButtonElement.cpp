#include "ButtonElement.h"

ButtonElement::ButtonElement(GUIContainer* container, sf::Texture* up, sf::Texture* down, sf::Texture* over, sf::Vector2f pos, sf::Vector2f size) : up(up), down(down), over(over)
{
	setContainer(container);
	setSprite(new sf::Sprite(*up));
	setPosition(pos);
	setSize(size);
	setVisible(true);
}

ButtonElement::ButtonElement(GUIContainer* container, std::string up, std::string down, std::string over, sf::Vector2f pos, sf::Vector2f size)
{
	sf::Texture* upTexture = new sf::Texture();
	upTexture->loadFromFile(up);
	sf::Texture* downTexture = new sf::Texture();
	upTexture->loadFromFile(down);
	sf::Texture* overTexture = new sf::Texture();
	upTexture->loadFromFile(over);

	ButtonElement(container, upTexture, upTexture, upTexture, pos, size);
}

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	if (isCursorOver(cursorPos))
	{
		getSprite()->setTexture(*down);
		isDown = true;
	}
}

void ButtonElement::mouseReleased(sf::Mouse::Button button)
{
	if (isDown)
	{
		getSprite()->setTexture(*up);
	}
	isDown = false;
}

void ButtonElement::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;
	if (isCursorOver(cursorPos) && !isDown)
	{
		getSprite()->setTexture(*over);
	}
}
