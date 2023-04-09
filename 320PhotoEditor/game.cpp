#include "game.h"


void game::initVar()
{
	this->endGame = false;
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
	this->player.update(this->window);
}

void game::render()
{
	this->window->clear();

	this->player.render(this->window);

	this->window->display();
}
