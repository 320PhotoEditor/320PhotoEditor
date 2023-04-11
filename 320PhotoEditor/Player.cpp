#include "Player.h"

void Player::initVar()
{
	this->moveSpeed = 13.f;
	this->accel = .5f;
	this->decel = 0.97f;
	this->velocity = sf::Vector2f(0.f, 0.f);
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setSize(sf::Vector2f(16.f, 16.f));
}

Player::Player()
{
	//Player will always start at the center of the window
	this->shape.setPosition(sf::Vector2f(615.f, 375.f));

	this->initVar();
	this->initShape();
}

Player::~Player()
{

}

void Player::updateInput()
{	//Accelerate or decelerate left or right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= accel;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += accel;
	}
	// If A or D is not being pressed slow player down gradually on the x-axis
	else
	{
		velocity.x *= decel;
	}
	// Accelerate or decelerate up and down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= accel;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += accel;
	}
	// If W or S is not being pressed slow player gradually on the y-axis
	else
	{
		velocity.y *= decel;
	}

	// Get actual velocity
	currentSpeed = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));
	
	// Check that actual velocity is not to fast
	if (currentSpeed > moveSpeed)
	{
		// Scale x and y speed
		velocity *= (moveSpeed / currentSpeed);
	}

	this->shape.move(velocity.x, velocity.y);

}

void Player::playerBounce(sf::Vector2f currentVel)
{
	this->velocity.x = -currentVel.x;
	this->velocity.y = -currentVel.y;
}

// Used to get current bounds of player object for pixel collision detection
sf::RectangleShape& Player::getCurrShape()
{
	return this->shape;
}

void Player::playerWindowColl(sf::RenderTarget* target)
{
	//Handle collision with window edge
	//TO DO: figure out why player can escape at the corners
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	if (playerBounds.left <= 0.f)
	{
		this->shape.setPosition(0.f, playerBounds.top);
		this->playerBounce(sf::Vector2f(this->velocity.x, -this->velocity.y));
	}
	if (playerBounds.left + playerBounds.width >= target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
		this->playerBounce(sf::Vector2f(this->velocity.x, -this->velocity.y));
	}
	if (playerBounds.top <= 0)
	{
		this->shape.setPosition(playerBounds.left, 0.f);
		this->playerBounce(sf::Vector2f(-this->velocity.x, this->velocity.y));
	}
	if (playerBounds.top + playerBounds.height >= target->getSize().y)
	{
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
		this->playerBounce(sf::Vector2f(-this->velocity.x, this->velocity.y));
	}
}

void Player::update(sf::RenderTarget* target)
{	
	//Player movement
	this->updateInput();
	this->playerWindowColl(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
