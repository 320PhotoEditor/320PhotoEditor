#include "Pixels.h"


void Pixels::initVar()
{
	// Want pixels to have a slower top speed than the player
	this->moveSpeed = 9.f;
	this->velocity = sf::Vector2f(0.f,0.f);
}

void Pixels::initShape()
{
	float size = static_cast <float> (rand() % 40 + 10);
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

// Used to get current bounds of pixel object for player collision detection
sf::RectangleShape& Pixels::getCurrShape()
{
	return this->shape;
}

// Takes the players velocity and assigns it to pixel
void Pixels::bounceOffPLayer(sf::Vector2f pixelVel, sf::Vector2f impulse, sf::Vector2f pixelSize)
{
	// VB' = VB + J / massB
	this->velocity = (pixelVel + impulse) / pixelSize.x;
	
	
	// OLD
	//pixel will get player velocity +/- based on size ratio playerSize/pixelSize
	//this->velocity -= (playerVel * (playerSize.x / pixelSize.x));
	//this->shape.setSize(sf::Vector2f(this->shape.getSize().x - 2, this->shape.getSize().y - 2));
}

// Helper function for bouncing off of window edge
void Pixels::bounceOffWindow(sf::Vector2f currentVel)
{
	this->velocity.x = -currentVel.x;
	this->velocity.y = -currentVel.y;
}

// Checking if pixel is at edge of window
void Pixels::pixelWindowColl(sf::RenderTarget* target)
{
	sf::FloatRect pixelBounds = this->shape.getGlobalBounds();
	// If hitting left edge reverse x-velocity, y-velocity remains the same
	if (pixelBounds.left <= 0.f)
	{
		this->shape.setPosition(0.f, pixelBounds.top);
		this->bounceOffWindow(sf::Vector2f(this->velocity.x, -this->velocity.y));
	}
	// If hitting right edge reverse x-velocity, y-velocity remains the same
	if (pixelBounds.left + pixelBounds.width >= target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - pixelBounds.width, pixelBounds.top);
		this->bounceOffWindow(sf::Vector2f(this->velocity.x, -this->velocity.y));
	}
	// If hitting top edge reverse y-velocity, x-velocity remains the same
	if (pixelBounds.top <= 0)
	{
		this->shape.setPosition(pixelBounds.left, 0.f);
		this->bounceOffWindow(sf::Vector2f(-this->velocity.x, this->velocity.y));
	}
	// If hitting bottom edge reverse y-velocity, x-velocity remains the same
	if (pixelBounds.top + pixelBounds.height >= target->getSize().y)
	{
		this->shape.setPosition(pixelBounds.left, target->getSize().y - pixelBounds.height);
		this->bounceOffWindow(sf::Vector2f(-this->velocity.x, this->velocity.y));
	}
}

void Pixels::update()
{
	// Get actual velocity
	currentSpeed = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));

	// Check that actual velocity is not to fast
	if (currentSpeed > moveSpeed)
	{
		// Since no input other than collisions allow pixel to move faster than max briefly
		velocity *= 0.97f;
	}

	this->shape.move(velocity.x, velocity.y);
}

void Pixels::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
