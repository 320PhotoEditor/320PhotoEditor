#include "Pixels.h"


void Pixels::initVar()
{
	// Want pixels to have a slower top speed than the player
	this->moveSpeed = 10.f;
}

void Pixels::initShape()
{
	float size = static_cast <float> (rand() % 30 + 10);
	this->shape.setFillColor(sf::Color::White);
	this->shape.setSize(sf::Vector2f(size,size));
}

Pixels::Pixels()
{	
	this->initVar();
	this->initShape();

	// Set position based on window size and shape size, probably don't want to hardcode screen size in the future
	float x = static_cast <float> (rand() % 1281 - this->shape.getGlobalBounds().width);
	float y = static_cast <float> (rand() % 801 - this->shape.getGlobalBounds().height);

	if (x < 0)
	{
		x = 0.f;
	}

	if (y < 0)
	{
		y = 0.f;
	}

	this->shape.setPosition(sf::Vector2f(x,y));
}

Pixels::~Pixels()
{

}

void Pixels::update()
{

}

void Pixels::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
