#include "Player.h"

void Player::initVar()
{
	this->moveSpeed = 8.f;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setSize(sf::Vector2f(25.f, 25.f));
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
{
	//Move player left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->moveSpeed, 0.f);
	}
	//Move player right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->moveSpeed, 0.f);
	}
	//Move player up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->moveSpeed);
	}
	//Move player down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->moveSpeed);
	}
}

void Player::update()
{
	//Player movement
	this->updateInput();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
