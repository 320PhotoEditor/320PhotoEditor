#include "Tool.h"

Tool::Tool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : up(up), down(down), over(over)
{
}

void Tool::setContainer(GUIContainer* container)
{
	this->container = container;
}

GUIContainer* Tool::getContainer()
{
	return container;
}

void Tool::setMenu(ApplicationMenu* applicationMenu)
{
	this->applicationMenu = applicationMenu;
}
