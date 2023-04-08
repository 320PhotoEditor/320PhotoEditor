#include "game.h"


void game::initVar()
{
	this->endGame = false;

}

void game::initWin()
{
	this->vm = sf::VideoMode(1280, 800);
	this->window = new sf::RenderWindow(this->vm, "Pixel Eater", sf::Style::Close | sf::Style::Titlebar);

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