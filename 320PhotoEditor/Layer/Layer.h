#pragma once

#include "../Common.h"

//basically in image that we edit
//dont create directly
class Layer
{
public:

	Layer(sf::Vector2u size, sf::Color color, sf::RenderWindow* renderWindow);

	sf::Image* getImage();

	sf::Sprite* getSprite();

	sf::Vector2i cursorToPixel(sf::Vector2i cursorPos);
	bool isCursorOver(sf::Vector2i cursorPos);

	//reloads the image to render
	void reload();

	~Layer();

private:

	sf::RenderWindow* renderWindow;

	sf::Texture texture;
	sf::Sprite* sprite;

	sf::Image* image;

	bool visible;
};

