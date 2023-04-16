#include "game.h"


void game::initVar()
{
	this->endGame = false;
	this->spawnTimeMax = 10.f;
	this->spawnTimer = this->spawnTimeMax;
	this->maxPixels = 8;
	this->restitutionCo = 0.f;
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

		float playerSize = this->player.getCurrShape().getSize().x;
		sf::Vector2f playerVel = this->player.velocity;
		sf::Vector2f playerPos = this->player.getCurrShape().getPosition();
		sf::RectangleShape playerAABB = sf::RectangleShape(sf::Vector2f(playerSize + 10, playerSize + 10 ));
		playerAABB.setPosition(sf::Vector2f(playerPos.x + playerVel.x, playerPos.y + playerVel.y));

		float pixelSize = this->Pixel[i].getCurrShape().getSize().x;
		sf::Vector2f pixelVel = this->Pixel[i].velocity;
		sf::Vector2f pixelPos = this->Pixel[i].getCurrShape().getPosition();
		sf::RectangleShape pixelAABB = sf::RectangleShape(sf::Vector2f(pixelSize + 10, pixelSize + 10 ));
		pixelAABB.setPosition(sf::Vector2f(pixelPos.x + pixelVel.x, pixelPos.y + pixelVel.y ));


		if (playerAABB.getGlobalBounds().intersects(pixelAABB.getGlobalBounds()))
		{
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
			{
				float playerPosx = this->player.getCurrShape().getPosition().x;
				float playerPosy = this->player.getCurrShape().getPosition().y;
				float playerWidth = this->player.getCurrShape().getSize().x;
				float playerHeight = this->player.getCurrShape().getSize().y;

				float pixelPosx = Pixel[i].getCurrShape().getPosition().x;
				float pixelPosy = Pixel[i].getCurrShape().getPosition().y;
				float pixelWidth = Pixel[i].getCurrShape().getSize().x;
				float pixelHeight = Pixel[i].getCurrShape().getSize().y;

				// If pixel and player ever intersect set new pixel position, and reverse pixel velocity.
				// Should really only happen when pixels spawn in.
				if (playerPosx < (pixelPosx + (pixelWidth / 2)))
				{
					Pixel[i].getCurrShape().setPosition(sf::Vector2f((pixelPosx - playerPosx) + pixelPosx, pixelPosy));
					Pixel[i].velocity.x = 2.f;
				}
				else
				{
					Pixel[i].getCurrShape().setPosition(sf::Vector2f(pixelPosx - (playerPosx - pixelPosx), pixelPosy));
					Pixel[i].velocity.x = -2.f;
				}

				if (playerPosy < (pixelPosy + (pixelHeight / 2)))
				{
					Pixel[i].getCurrShape().setPosition(sf::Vector2f(pixelPosx, (pixelPosy - playerPosy) + pixelPosy));
					Pixel[i].velocity.y = 2.f;
				}
				else
				{
					Pixel[i].getCurrShape().setPosition(sf::Vector2f(pixelPosx, pixelPosy - (playerPosy - pixelPosy)));
					Pixel[i].velocity.y = -2.f;
				}
			}
			else
			{

				//sf::Vector2f relativeVel = this->player.velocity - Pixel[i].velocity;
				sf::Vector2f relativeVel = Pixel[i].velocity - this->player.velocity;

				sf::Vector2f side1 = sf::Vector2f(minkowskiAABB.left, minkowskiAABB.top + minkowskiAABB.height) -
					sf::Vector2f(minkowskiAABB.left, minkowskiAABB.top);

				// Cross products
				float numerator1 = minkowskiAABB.left * relativeVel.y - minkowskiAABB.top * relativeVel.x;
				float denominator1 = relativeVel.x * side1.y - relativeVel.y * side1.x;
				float t1 = 0;
				float u1 = 0;
				

				if (numerator1 == 0 && denominator1 == 0)
				{
					// Side being considered is co-linear with relative velocity vector,
					// this occurence should be extremely extremely rare so I am not dealing with 
					// it right now.
					t1 = INFINITY;
				}
				else if (denominator1 == 0)
				{
					// Lines are parallel
					t1 = INFINITY;
				}
				else
				{
					u1 = numerator1 / denominator1;
					t1 = (minkowskiAABB.left * side1.y - minkowskiAABB.top * side1.x) / denominator1;
				}

				if (t1 >= 0 && t1 <= 1 && u1 >= 0 && u1 <= 1)
				{
					// Let t1 stand
				}
				else
				{
					t1 = INFINITY;
				}


				sf::Vector2f side2 = sf::Vector2f(minkowskiAABB.left + minkowskiAABB.width, minkowskiAABB.top + minkowskiAABB.height) -
					sf::Vector2f(minkowskiAABB.left, minkowskiAABB.top + minkowskiAABB.height);

				// Cross products
				// AABB min x max y cross relative max x max y
				float numerator2 = minkowskiAABB.left * relativeVel.y - (minkowskiAABB.top + minkowskiAABB.height) * relativeVel.x;
				float denominator2 = relativeVel.x * side2.y - relativeVel.y * side2.x;
				float t2 = 0;
				float u2 = 0;


				if (numerator2 == 0 && denominator2 == 0)
				{
					// Side being considered is co-linear with relative velocity vector,
					// this occurence should be extremely extremely rare so I am not dealing with 
					// it right now.
					t2 = INFINITY;
				}
				else if (denominator2 == 0)
				{
					// Lines are parallel
					t2 = INFINITY;
				}
				else
				{
					u2 = numerator2 / denominator2;
					t2 = (minkowskiAABB.left * side2.y - (minkowskiAABB.top + minkowskiAABB.height) * side2.x) / denominator2;
				}

				if (t2 >= 0 && t2 <= 1 && u2 >= 0 && u2 <= 1)
				{
					// Let t2 stand
				}
				else
				{
					t2 = INFINITY;
				}


				sf::Vector2f side3 = sf::Vector2f(minkowskiAABB.left + minkowskiAABB.width, minkowskiAABB.top) -
					sf::Vector2f(minkowskiAABB.left + minkowskiAABB.width, minkowskiAABB.top + minkowskiAABB.height);

				// Cross products
				float numerator3 = (minkowskiAABB.left + minkowskiAABB.width) * relativeVel.y -
					(minkowskiAABB.top + minkowskiAABB.height) * relativeVel.x;
				float denominator3 = relativeVel.x * side3.y - relativeVel.y * side3.x;
				float t3 = 0;
				float u3 = 0;

				if (numerator3 == 0 && denominator3 == 0)
				{
					// Side being considered is co-linear with relative velocity vector,
					// this occurence should be extremely extremely rare so I am not dealing with 
					// it right now.
					t3 = INFINITY;
				}
				else if (denominator3 == 0)
				{
					// Lines are parallel
					t3 = INFINITY;
				}
				else
				{
					u3 = numerator3 / denominator3;
					t3 = ((minkowskiAABB.left + minkowskiAABB.width) * side3.y -
						(minkowskiAABB.top + minkowskiAABB.height) * side3.x) /
						denominator3;
				}

				if (t3 >= 0 && t3 <= 1 && u3 >= 0 && u3 <= 1)
				{
					// Let t3 stand
				}
				else
				{
					t3 = INFINITY;
				}




				sf::Vector2f side4 = sf::Vector2f(minkowskiAABB.left, minkowskiAABB.top) -
					sf::Vector2f(minkowskiAABB.left + minkowskiAABB.width, minkowskiAABB.top);

				// Cross products
				float numerator4 = (minkowskiAABB.left + minkowskiAABB.width) * relativeVel.y -
					minkowskiAABB.top * relativeVel.x;
				float denominator4 = relativeVel.x * side4.y - relativeVel.y * side4.x;
				float t4 = 0;
				float u4 = 0;

				if (numerator4 == 0 && denominator4 == 0)
				{
					// Side being considered is co-linear with relative velocity vector,
					// this occurence should be extremely extremely rare so I am not dealing with 
					// it right now.
					t4 = INFINITY;
				}
				else if (denominator4 == 0)
				{
					// Lines are parallel
					t4 = INFINITY;
				}
				else
				{
					u4 = numerator4 / denominator4;
					t4 = ((minkowskiAABB.left + minkowskiAABB.width) * side4.y -
						minkowskiAABB.top * side4.x) / denominator4;
				}

				if (t4 >= 0 && t4 <= 1 && u4 >= 0 && u4 <= 1)
				{
					// Let t4 stand
				}
				else
				{
					t4 = INFINITY;
				}

				float mint12 = std::min(t1, t2);
				float mint34 = std::min(t3, t4);
				float t = std::min(mint12, mint34);

				if (t < INFINITY)
				{
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

					sf::Vector2f playerOrigVel = this->player.velocity;
					sf::Vector2f pixelOrigVel = Pixel[i].velocity;


					this->player.velocity = this->player.velocity * (t);
					Pixel[i].velocity = Pixel[i].velocity * (t);

					
					//Player will be the A
					sf::Vector2f playerPos = this->player.getCurrShape().getPosition();

					// Pixel will be the B
					sf::Vector2f pixelPos = this->Pixel[i].getCurrShape().getPosition();

					// Probably doesn't make a difference, but wanted the centersVector to be based on the actual centers of the objects
					sf::Vector2f playerActualCen = sf::Vector2f(playerPos.x + (this->player.getCurrShape().getGlobalBounds().width / 2.f),
						playerPos.y + (this->player.getCurrShape().getGlobalBounds().height / 2.f));

					sf::Vector2f pixelActualCen = sf::Vector2f(pixelPos.x + (this->Pixel[i].getCurrShape().getGlobalBounds().width / 2.f),
						pixelPos.y + (this->Pixel[i].getCurrShape().getGlobalBounds().height / 2.f));

					sf::Vector2f interimCenter = (pixelActualCen - playerActualCen);

					// centersVector is the n for the impulse equation
					sf::Vector2f centersVector = interimCenter / sqrt(abs(interimCenter.x * interimCenter.x)
						+ abs(interimCenter.y + interimCenter.y));


					/*
					//Impulse J = -(1 + e) * (VA · n - VB · n) / (1 / massA + 1 / massB)
					sf::Vector2f impulse = -(1 + this->restitutionCo) * ((playerOrigVel * centersVector) - (pixelOrigVel
						* centersVector)) / ((1 / this->player.getCurrShape().getSize().x) + (1 / this->Pixel[i].getCurrShape().getSize().x));
					*/
					

					float playerNewxVel = (playerOrigVel.x * (playerSize - pixelSize) + (2 * pixelSize * pixelOrigVel.x))
						/ (playerSize + pixelSize);
					float playerNewyVel = (playerOrigVel.y * (playerSize - pixelSize) + (2 * pixelSize * pixelOrigVel.y))
						/ (playerSize + pixelSize);
					float pixelNewxVel = (pixelOrigVel.x * (pixelSize - playerSize) + (2 * playerSize * playerOrigVel.x))
						/ (playerSize + pixelSize);
					float pixelNewyVel = (pixelOrigVel.y * (pixelSize - playerSize) + (2 * playerSize * playerOrigVel.y))
						/ (playerSize + pixelSize);
					
					this->player.velocity = sf::Vector2f(playerNewxVel, playerNewyVel);

					Pixel[i].velocity = sf::Vector2f(pixelNewxVel, pixelNewyVel);

					// If pixel is smaller than player, pixel loses mass, player does not
					if (this->Pixel[i].getCurrShape().getSize().x < (this->player.getCurrShape().getSize().x))
					{
						// Spawns pixel off of pixel involved in collision
						this->Pixel.push_back(Pixels(pixelActualCen, playerOrigVel));
						this->Pixel[i].loseMass();
					}

					// If pixel is less than twice the size of the player both lose mass
					if ((this->Pixel[i].getCurrShape().getSize().x < this->player.getCurrShape().getSize().x * 2.f) &&
						(this->Pixel[i].getCurrShape().getSize().x >= this->player.getCurrShape().getSize().x))
					{
						this->Pixel.push_back(Pixels(pixelActualCen, playerOrigVel));
						this->Pixel[i].loseMass();
						//Don't spawn pixel in player!
						//this->Pixel.push_back(Pixels(playerActualCen, this->Pixel[i].velocity));
						//this->player.loseMass();
					}

					// If pixel is twice as large or larger than player loses mass
					if (this->Pixel[i].getCurrShape().getSize().x > (this->player.getCurrShape().getSize().x * 2.f))
					{
						//Spawning a pixel inside the player is a bad idea
						//this->Pixel.push_back(Pixels(playerActualCen, this->Pixel[i].velocity));
						//this->player.loseMass();
					}

					/*
					//If player hits a pixel block, pixel gets some fraction of players velocity
					this->Pixel[i].bounceOffPLayer(
						// VB' = VB + J / massB
						pixelOrigVel,
						impulse,
						this->Pixel[i].getCurrShape().getSize()

						// Part of the old method that wasn't working very well
						//this->player.velocity,
						//this->player.getCurrShape().getSize(),
						//this->Pixel[i].getCurrShape().getSize()
					);

					this->player.bounceOffPixel(
						// VA' = VA - J / massA
						playerOrigVel,
						impulse,
						this->player.getCurrShape().getSize()

						// OLD
						//this->Pixel[i].velocity,
						//this->player.getCurrShape().getSize(),
						//this->Pixel[i].getCurrShape().getSize()
					);
					*/
				}
			}
		}
	}
}
