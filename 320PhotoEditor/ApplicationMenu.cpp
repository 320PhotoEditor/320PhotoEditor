#include "ApplicationMenu.h"
#include "Tool/ToolManager.h"

ApplicationMenu::ApplicationMenu(sf::RenderWindow* renderWindow, LayerManager* layerManager, ToolManager* toolManager)
{
	this->renderWindow = renderWindow;
	this->layerManager = layerManager;
	this->toolManager = toolManager;

	menuContainer = new GUIContainer({ 0, 0 }, { 1, 0.025 }, renderWindow);
	colorContainer = new GUIContainer({ 0, 0.325 }, { 0.2, 0.4 }, renderWindow);

	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	fileMenuButton = new ButtonElement(upTexture, downTexture, overTexture);
	fileMenuButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	menuContainer->addElement(fileMenuButton);
	fileMenuButton->setSize({ 0.05, 1 });
	fileMenuButton->setPosition({ 0, 0 });

	newBlankButton = new ButtonElement(upTexture, downTexture, overTexture);
	newBlankButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	menuContainer->addElement(newBlankButton);
	newBlankButton->setSize({ 0.05, 1 });
	newBlankButton->setPosition({ 0.05, 0 });

	newTransparentButton = new ButtonElement(upTexture, downTexture, overTexture);
	newTransparentButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	menuContainer->addElement(newTransparentButton);
	newTransparentButton->setSize({ 0.05, 1 });
	newTransparentButton->setPosition({ 0.1, 0 });

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

	sf::Image whiteImage;
	whiteImage.create(1, 1, sf::Color::White);

	foreColorTexture = new sf::Texture();
	foreColorTexture->loadFromImage(whiteImage);
	backColorTexture = new sf::Texture();
	backColorTexture->loadFromImage(whiteImage);

	foregroundColor = new ButtonElement(foreColorTexture, foreColorTexture, foreColorTexture);
	foregroundColor->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	colorContainer->addElement(foregroundColor);
	foregroundColor->setSize({ 0.25, 0.125 });
	foregroundColor->setPosition({ 0.25, 0.5 });
	foregroundColor->setColor(getForegroundColor());

	backgroundColor = new ButtonElement(backColorTexture, backColorTexture, backColorTexture);
	backgroundColor->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	colorContainer->addElement(backgroundColor);
	backgroundColor->setSize({ 0.25, 0.125 });
	backgroundColor->setPosition({ 0.5, 0.5 });
	backgroundColor->setColor(getBackgroundColor());

	colorPicker = new ColorPickerElement();
	colorPicker->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
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

sf::Color ApplicationMenu::getForegroundColor()
{
	return foreColor;
}

sf::Color ApplicationMenu::getBackgroundColor()
{
	return backColor;
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

	if (button == colorPicker)
	{
		if (foreSelect)
		{
			foreColor = colorPicker->getPickedColor();
			foregroundColor->setColor(foreColor);
		}
		else
		{
			backColor = colorPicker->getPickedColor();
			backgroundColor->setColor(backColor);
		}
		return;
	}

	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}

	if (button == fileMenuButton)
	{
		std::string filename = openFileDialog(renderWindow);

		//check if file exists before attempting load
		std::ifstream test(filename);
		if (!test)
		{
			std::cerr << "Error: invalid file name\n";
			return;
		}
		test.close();

		//layerManager->removeSelectedLayer();
		layerManager->createLayerFromFile(filename);
		toolManager->setSelectedLayer(layerManager->getSelectedLayer());
		toolManager->restartTool();
	}
	else if (button == newBlankButton)
	{
		layerManager->createLayer(sf::Color::White);
		toolManager->setSelectedLayer(layerManager->getSelectedLayer());
		toolManager->restartTool();
	}
	else if (button == newTransparentButton)
	{
		layerManager->createLayer(sf::Color(255, 255, 255, 0));
		toolManager->setSelectedLayer(layerManager->getSelectedLayer());
		toolManager->restartTool();
	}
	else if (button == incrLightness)
	{
		colorPicker->setLightness(std::min(colorPicker->getLightness() + 0.05, 1.0));
	}
	else if (button == decrLightness)
	{
		colorPicker->setLightness(std::max(colorPicker->getLightness() - 0.05, 0.0));
	}
	else if (button == foregroundColor)
	{
		foreSelect = true;
	}
	else if (button == backgroundColor)
	{
		foreSelect = false;
	}
}
