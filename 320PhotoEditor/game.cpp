#include "game.h"


void game::initVar()
{
	this->endGame = false;
	this->spawnTimeMax = 10.f;
	this->spawnTimer = this->spawnTimeMax;
	this->maxPixels = 12;
	this->restitutionCo = 0.25f;
}

void game::initWin()
{
	this->vm = sf::VideoMode(1280, 800);
	this->window = new sf::RenderWindow(this->vm, "Pixel Eater", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

game::game()
{
	this->initVar();
	this->initWin();
}

game::~game()
{
	delete this->window;
}

const bool game::running() const
{
	return this->window->isOpen();
}

void game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
				{
					this->window->close();
				}
				break;
		}
	}
}

void game::update()
{
	this->pollEvents();
	this->spawnPixels();
	this->playerPixelColl();
	this->player.update(this->window);
	

	// Checks each pixel for window collision and updates
	for (auto& pixel : this->Pixel)
	{
		pixel.pixelWindowColl(this->window);
		pixel.update();
	}
}

// Renders each element belonging to the window
void game::render()
{
	this->window->clear();

	// Render the PC
	this->player.render(this->window);

	// Render each pixel in turn
	for (auto i : this->Pixel)
	{
		i.render(*this->window);
	}

	this->window->display();
}

// Counts to spawn time max, at max checks to see if more pixels are needed
void game::spawnPixels()
{
	sf::Vector2f spawnDefault = sf::Vector2f(0.f, 0.f);
	if (this->spawnTimer < this->spawnTimeMax)
	{
		this->spawnTimer += 1.f;
	}
	else
	{
		if (this->Pixel.size() < this->maxPixels)
		{
			this->Pixel.push_back(Pixels(spawnDefault, spawnDefault));
			this->spawnTimer = 0.f;
		}
	}
}

void game::playerPixelColl()
{
	// For each pixel that exists
	for (size_t i = 0; i < this->Pixel.size(); i++)
	{
		// Check if player is colliding with any of the pixels
		// TO DO: Fix clipping issue
		// TO DO: Fix odd angles of deflection (changed impulse based method of calculating deflection made a small improvement but the
		// objects clipping into each other might be the orimary cause.)
		sf::FloatRect area;
		if (this->player.getCurrShape().getGlobalBounds().intersects(this->Pixel[i].getCurrShape().getGlobalBounds(), area))
		{

			//Player will be the A
			sf::Vector2f playerPos = this->player.getCurrShape().getPosition();
			// Pixel will be the B
			sf::Vector2f pixelPos = this->Pixel[i].getCurrShape().getPosition();
			// Probably doesn't make a difference, but wanted the centersVector to be based on the actual centers of the objects
			sf::Vector2f playerActualCen = sf::Vector2f(playerPos.x + (this->player.getCurrShape().getGlobalBounds().width/2.f),
				playerPos.y + (this->player.getCurrShape().getGlobalBounds().height/2.f));
			sf::Vector2f pixelActualCen = sf::Vector2f(pixelPos.x + (this->Pixel[i].getCurrShape().getGlobalBounds().width / 2.f),
				pixelPos.y + (this->Pixel[i].getCurrShape().getGlobalBounds().height/2.f));
			sf::Vector2f interimCenter = (pixelActualCen - playerActualCen);
			// centersVector is the n for the impulse equation
			sf::Vector2f centersVector = interimCenter / sqrt(abs(interimCenter.x * interimCenter.x) 
				+ abs(interimCenter.y + interimCenter.y));

			//Impulse J = -(1 + e) * (VA · n - VB · n) / (1 / massA + 1 / massB)
			sf::Vector2f impulse = -(1 + this->restitutionCo) * ((this->player.velocity * centersVector) - (this->Pixel[i].velocity
				* centersVector)) / ((1 / this->player.getCurrShape().getSize().x) + (1 / this->Pixel[i].getCurrShape().getSize().x));

			if (this->Pixel[i].getCurrShape().getSize().x < (this->player.getCurrShape().getSize().x / 2))
			{
				// Delete pixel object
				this->Pixel.erase(this->Pixel.begin() + i);
				// Make a call to eat
				this->player.eatPixel();
				// break
				break;
			}

			this->Pixel.push_back(Pixels(pixelActualCen, this->player.velocity));
			
			//If player hits a pixel block, pixel gets some fraction of players velocity
			this->Pixel[i].bounceOffPLayer(
				// VB' = VB + J / massB
				this->Pixel[i].velocity,
				impulse,
				this->Pixel[i].getCurrShape().getSize()
				
				
				// Part of the old method that wasn't working very well
				//this->player.velocity,
				//this->player.getCurrShape().getSize(),
				//this->Pixel[i].getCurrShape().getSize()
			);

			this->player.bounceOffPixel(
				// VA' = VA - J / massA
				this->player.velocity,
				impulse,
				this->player.getCurrShape().getSize()
				
				
				// OLD
				//this->Pixel[i].velocity,
				//this->player.getCurrShape().getSize(),
				//this->Pixel[i].getCurrShape().getSize()
			);
		}
	}
}
