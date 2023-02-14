#pragma once

#include "../Common.h"
#include "../InputListener.h"
#include "../Layer/Layer.h"
#include "../GUI/GUIContainer.h"
#include "../ApplicationMenu.h"

class Tool : public InputListener
{
public:

	Tool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

	virtual void init() = 0;
	virtual void start(Layer* layer) = 0;
	virtual void stop() = 0;
	virtual void run() = 0;

	//textures for button icon
	sf::Texture* up;
	sf::Texture* down;
	sf::Texture* over;

	void setContainer(GUIContainer* container);
	GUIContainer* getContainer();

	void setMenu(ApplicationMenu* applicationMenu);

protected:

	GUIContainer* container;
	ApplicationMenu* applicationMenu;
};

