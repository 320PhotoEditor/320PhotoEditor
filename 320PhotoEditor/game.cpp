#include "game.h"


void game::initVar()
{
	this->endGame = false;
	this->spawnTimeMax = 10.f;
	this->spawnTimer = this->spawnTimeMax;
	this->maxPixels = 10;
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
	this->player.update(this->window);
}

void game::render()
{
	this->window->clear();

	this->player.render(this->window);

	for (auto i : this->Pixel)
	{
		i.render(*this->window);
	}

	this->window->display();
}

void game::spawnPixels()
{
	if (this->spawnTimer < this->spawnTimeMax)
	{
		this->spawnTimer += 1.f;
	}
	else
	{
		if (this->Pixel.size() < this->maxPixels)
		{
			this->Pixel.push_back(Pixels());
			this->spawnTimer = 0.f;
		}
	}
}
