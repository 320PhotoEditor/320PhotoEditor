#pragma once

#include "../Common.h"
#include "../InputListener.h"

class Tool : public InputListener
{
public:

	Tool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	virtual void start(sf::Image* layer) = 0;
	virtual void stop() = 0;
	virtual void run() = 0;

	//textures for button icon
	sf::Texture* up;
	sf::Texture* down;
	sf::Texture* over;

private:
};

