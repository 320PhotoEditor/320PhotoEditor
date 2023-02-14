/*#include "ImageButton.h"
#include "../GUI/GUIElement.h"

// To do: maybe move away from the tool constructor
ImageButton::ImageButton(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void ImageButton::init()
{

    // To do: loop through cwd?? assigning available images to individual buttons
    sf::Texture* upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture* downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture* overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    selectButton = new ButtonElement(upTexture, downTexture, overTexture);
    selectButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    selectButton->setSize({ .25, .25 });
    selectButton->setPosition({ 0.5, 0 });
}

void ImageButton::start(Layer* layer)
{
    this->layer = layer;
}

void ImageButton::buttonPressed(GUIElement* button, int status)
{
    // Code for storing image selection going here.
}*/
