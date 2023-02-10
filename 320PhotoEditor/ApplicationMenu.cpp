#include "ApplicationMenu.h"

ApplicationMenu::ApplicationMenu(sf::RenderWindow* renderWindow, LayerManager* layerManager)
{
	this->layerManager = layerManager;

	menuContainer = new GUIContainer({0, 0}, {1, 0.025}, renderWindow);

	sf::Texture* upTexture = new sf::Texture();
	upTexture->loadFromFile("../assets/button_up.png");
	sf::Texture* downTexture = new sf::Texture();
	downTexture->loadFromFile("../assets/button_down.png");
	sf::Texture* overTexture = new sf::Texture();
	overTexture->loadFromFile("../assets/button_over.png");

	fileMenuButton = new ButtonElement(upTexture, downTexture, overTexture);
	fileMenuButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	menuContainer->addElement(fileMenuButton);
	fileMenuButton->setSize({ 0.05, 1 });
	fileMenuButton->setPosition({ 0, 0 });
}

ApplicationMenu::~ApplicationMenu()
{
}

void ApplicationMenu::update()
{
	menuContainer->render();
}

GUIContainer* ApplicationMenu::getGUIContainer()
{
	return menuContainer;
}

void ApplicationMenu::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}


	//TODO: add some sort of open file dialog
	//for now just type in the file path
	std::string filename = "";

	if (button == fileMenuButton)
	{
		//check if file exists before attempting load
		std::ifstream test(filename);
		if (!test)
		{
			std::cerr << "Error: invalid file name\n";
			return;
		}
		test.close();

		layerManager->getSelectedLayer()->getImage()->loadFromFile(filename);
	}
}
