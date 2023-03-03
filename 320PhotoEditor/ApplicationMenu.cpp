#include "ApplicationMenu.h"

ApplicationMenu::ApplicationMenu(sf::RenderWindow* renderWindow, LayerManager* layerManager)
{
	this->layerManager = layerManager;

	menuContainer = new GUIContainer({ 0, 0 }, { 1, 0.025 }, renderWindow);
	colorContainer = new GUIContainer({ 0, 0.325 }, { 0.2, 0.4 }, renderWindow);

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

	incrLightness = new ButtonElement(upTexture, downTexture, overTexture);
	incrLightness->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	colorContainer->addElement(incrLightness);
	incrLightness->setSize({ 0.25, 0.125 });
	incrLightness->setPosition({ 0.75, 0.5 });

	decrLightness = new ButtonElement(upTexture, downTexture, overTexture);
	decrLightness->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	colorContainer->addElement(decrLightness);
	decrLightness->setSize({ 0.25, 0.125 });
	decrLightness->setPosition({ 0, 0.5 });

	colorPicker = new ColorPickerElement();
	colorContainer->addElement(colorPicker);
	colorPicker->setSize({ 1, 0.5 });
	colorPicker->setPosition({ 0, 0 });
}

ApplicationMenu::~ApplicationMenu()
{
}

void ApplicationMenu::update()
{
	menuContainer->render();
	colorContainer->render();
}

//TODO: add way to change color for foreground and background specifically
//probably with buttons that change color
sf::Color ApplicationMenu::getForegroundColor()
{
	return colorPicker->getPickedColor();
}

sf::Color ApplicationMenu::getBackgroundColor()
{
	return colorPicker->getPickedColor();
}

GUIContainer* ApplicationMenu::getMenuContainer()
{
	return menuContainer;
}

GUIContainer* ApplicationMenu::getColorContainer()
{
	return colorContainer;
}

void ApplicationMenu::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}


	//TODO: add some sort of open file dialog
	//for now just type in the file path
	std::string filename = "C:\\Users\\User\\Desktop\\New Folder\\Sample_Image4.jpg";

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
		layerManager->getSelectedLayer()->reload();
	}
	else if (button == incrLightness)
	{
		colorPicker->setLightness(std::min(colorPicker->getLightness() + 0.05, 1.0));
		std::cout << colorPicker->getLightness() << std::endl;
	}
	else if (button == decrLightness)
	{
		colorPicker->setLightness(std::max(colorPicker->getLightness() - 0.05, 0.0));
		std::cout << colorPicker->getLightness() << std::endl;
	}
}
