#pragma once

#include "../Common.h"

//basically in image that we edit
//dont create directly
class Layer
{
public:
	Layer(sf::Vector2u size, sf::Color color, sf::RenderWindow* renderWindow);
	Layer(std::string filePath, sf::RenderWindow* renderWindow);

	//actual image data
	sf::Image* getImage();

	//a mask that can be used for selections
	//white used for selected and black for not selected
	sf::Image* getMask();
	
	sf::Texture* getMaskTexture();

	sf::Sprite* getSprite();

	sf::Vector2i cursorToPixel(sf::Vector2i cursorPos);
	bool isCursorOver(sf::Vector2i cursorPos);

	//reloads the image to render
	void reload();

	void reloadMask();

	//reloads the image from the texture on gpu
	void loadImageFromTexture();

	void loadMaskFromTexture();

	~Layer();

private:

	void createLayer(sf::Image* image, sf::RenderWindow* renderWindow);

	sf::RenderWindow* renderWindow;

	sf::Texture texture;
	sf::Texture maskTexture;
	sf::Sprite* sprite;

	sf::Image* image;
	sf::Image* mask;

	bool visible;
};

