#include "game.h"


void game::initVar()
{
	this->endGame = false;
	this->spawnTimeMax = 10.f;
	this->spawnTimer = this->spawnTimeMax;
	this->maxPixels = 8;
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
	this->playerPixelColl();
	this->pollEvents();
	this->spawnPixels();
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
		////
		// TO DO: Re-implement my broad phase sweeping, probably ought to check in the direction each object is moving
		//		  so maybe offset AABBs positions with the velocity vector which should give an image of where the object
		//		  will be in the next frame. This may lead to performance issues but I probably won't have tim to implement
		//		  anything fancier like a quadtree.
		////
		/*
		float playerSize = this->player.getCurrShape().getSize().x;
		sf::Vector2f playerVel = this->player.velocity;
		sf::Vector2f playerPos = this->player.getCurrShape().getPosition();
		sf::RectangleShape playerAABB = sf::RectangleShape(sf::Vector2f(playerSize + abs(playerVel.x) + 10, playerSize + abs(playerVel.y) + 10));
		playerAABB.setPosition(sf::Vector2f(playerPos.x - ((abs(playerVel.x) + 10) / 2), playerPos.y - ((abs(playerVel.y) + 10) / 2)));
		
		float pixelSize = this->Pixel[i].getCurrShape().getSize().x;
		sf::Vector2f pixelVel = this->Pixel[i].velocity;
		sf::Vector2f pixelPos = this->Pixel[i].getCurrShape().getPosition();
		sf::RectangleShape pixelAABB = sf::RectangleShape(sf::Vector2f(pixelSize + abs(pixelVel.x) + 10, pixelSize + abs(pixelVel.y) +10 ));
		pixelAABB.setPosition(sf::Vector2f(pixelPos.x - ((abs(pixelVel.x) + 10) / 2), pixelPos.y - ((abs(pixelVel.y) + 10) / 2)));
		*/

		//if (playerAABB.getGlobalBounds().intersects(pixelAABB.getGlobalBounds()))
		//{
			sf::FloatRect playerAABB = this->player.getCurrShape().getGlobalBounds();
			sf::FloatRect pixelAABB = Pixel[i].getCurrShape().getGlobalBounds();
			sf::FloatRect minkowskiAABB = sf::FloatRect(playerAABB.left - (pixelAABB.left + pixelAABB.width),
				playerAABB.top - (pixelAABB.top + pixelAABB.height),
				playerAABB.width + pixelAABB.width,
				playerAABB.height + pixelAABB.height);

			// If the minkowskiAABB contains the origin (0,0) then player is inside pixel.
			if (minkowskiAABB.top <= 0 &&
				minkowskiAABB.top + minkowskiAABB.height > 0 &&
				minkowskiAABB.left <= 0 &&
				minkowskiAABB.left + minkowskiAABB.width > 0)
			{	// TO DO: if pixel and player ever intersect set new player position, and reduce both velocities to zero
				this->player.velocity.x = this->player.velocity.x * -1;
				this->player.velocity.y = this->player.velocity.y * -1;
			}
			else
			{
				////
				// TO DO: Create relative velocity vector player.v - pixel[i].v
				//		  Check if vector intersects any of the four sides of the MinkowskiAABB.
				//		  If more than one intersection use the first.
				//		  Scale the player and pixel velocity with relative.v penetration/relative.v total length?
				//		  Call bounce functions on player and pixel based on original velocities
				////
			}

			/*
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

				// If pixel is less than half the size of player it gets eaten
				if (this->Pixel[i].getCurrShape().getSize().x <= (this->player.getCurrShape().getSize().x / 2.f))
				{
					// Delete pixel object
					this->Pixel.erase(this->Pixel.begin() + i);
					// Make a call to eat
					this->player.eatPixel();
					// break
					break;
				}

				// If pixel is smaller than player, pixel loses mass, player does not
				if (this->Pixel[i].getCurrShape().getSize().x < (this->player.getCurrShape().getSize().x))
				{
					// Spawns pixel off of pixel involved in collision
					this->Pixel.push_back(Pixels(pixelActualCen, this->player.velocity));
					this->Pixel[i].loseMass();
				}

				// If pixel is less than twice the size of the player both lose mass
				if ((this->Pixel[i].getCurrShape().getSize().x < this->player.getCurrShape().getSize().x * 2.f) &&
					(this->Pixel[i].getCurrShape().getSize().x >= this->player.getCurrShape().getSize().x))
				{
					this->Pixel.push_back(Pixels(pixelActualCen, this->player.velocity));
					this->Pixel[i].loseMass();
					//Don't spawn pixel in player!
					//this->Pixel.push_back(Pixels(playerActualCen, this->Pixel[i].velocity));
					this->player.loseMass();
				}

				// If pixel is twice as large or larger than player loses mass
				if (this->Pixel[i].getCurrShape().getSize().x > (this->player.getCurrShape().getSize().x * 2.f))
				{
					//Spawning a pixel inside the player is a bad idea
					//this->Pixel.push_back(Pixels(playerActualCen, this->Pixel[i].velocity));
					this->player.loseMass();
				}

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
				*/
			//}
	}
}
