#include "TestTool.h"

TestTool::TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void TestTool::start(Layer* layer)
{
	this->layer = layer;

    sf::Texture* upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture* downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture* overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
    button->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(button);

    button->setSize({ .25, .25 });

    button->setPosition({0, 0});
}

void TestTool::keyPressed(sf::Keyboard::Key key)
{
	layer->getImage()->setPixel(0, 0, sf::Color::Red); 
	layer->reload();
}
