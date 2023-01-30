#pragma once

#include "../Common.h"

class Tool
{
public:

	Tool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	void start();
	void stop();

	sf::Texture* up;
	sf::Texture* down;
	sf::Texture* over;

private:
};

