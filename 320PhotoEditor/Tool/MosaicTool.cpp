#include "MosaicTool.h"
#include "../GUI/GUIElement.h"

MosaicTool::MosaicTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void MosaicTool::init()
{
    sf::Texture* upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture* downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture* overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    selectButton = new ButtonElement(upTexture, downTexture, overTexture);
    selectButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(selectButton);
    selectButton->setSize({ .25, .25 });
    selectButton->setPosition({ 0.5, 0 });
}

void MosaicTool::start(Layer* layer)
{
    this->layer = layer;
}

void MosaicTool::buttonPressed(GUIElement* button, int status)
{
    std::cout << button << "\n";
    std::cout << selectButton << "\n";

    if (status != ButtonElement::ButtonState::DOWN)
    {
        return;
    }
    
if (button == selectButton) {

        newWindow = new sf::RenderWindow(sf::VideoMode(500,500), "Test");
        
        while (newWindow->isOpen())
        {
            sf::Event event;
            while (newWindow->pollEvent(event))
            {
                switch (event.type) {
                case sf::Event::Closed:
                    newWindow->close();
                    break;
                }
            }
        }
    }
}
