#include "FilterTool.h"


FilterTool::FilterTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void FilterTool::init()
{
    sf::Texture* upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture* downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture* overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    bwButton = new ButtonElement(upTexture, downTexture, overTexture);
    bwButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(bwButton);
    bwButton->setSize({ .25, .25 });
    bwButton->setPosition({ 0.25, 0.5 });

    windowButton = new ButtonElement(upTexture, downTexture, overTexture);
    windowButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(windowButton);
    windowButton->setSize({ .25, .25 });
    windowButton->setPosition({ 0.5, 0.5 });

    orangeButton = new ButtonElement(upTexture, downTexture, overTexture);
    orangeButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(orangeButton);
    orangeButton->setSize({ .25, .25 });
    orangeButton->setPosition({ 0.25, 0.75 });

    refreshButton = new ButtonElement(upTexture, downTexture, overTexture);
    refreshButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(refreshButton);
    refreshButton->setSize({ .25, .25 });
    refreshButton->setPosition({ 0.5, 0.75 });
}

void FilterTool::start(Layer* layer)
{
    this->layer = layer;
}

void FilterTool::mousePressed(sf::Mouse::Button button)
{

}


void FilterTool::buttonPressed(GUIElement* button, int status)
{
    if (button == bwButton)
    {
        int buttonPress = 0;
        sf::Color color;
        int a,b;
        for (a = 0; a < 500; a++)
        {
            for (b = 0; b < 500; b++)
            {
                sf::Color color2 = layer->getImage()->getPixel(a, b);
                int grayscale = ((color2.r * 0.299) + (color2.g * 0.587) + (color2.b * 0.114));
                layer->getImage()->setPixel(a, b, sf::Color(grayscale, grayscale, grayscale, 255));
            }
        }

        layer->reload();
    }

    if (button == windowButton)
    {
        sf::RenderWindow newWindow(sf::VideoMode(500, 500), "Zoom Window");
        while (newWindow.isOpen())
        {
            sf::Event event;
            while (newWindow.pollEvent(event))
            {
                switch (event.type) {
                    case sf::Event::Closed:
                        newWindow.close();
                        break;
                }
            }
        }
    }

    if (button == orangeButton)
    {
        int a,b;
        for (a = 0; a < 500; a++)
        {
            for (b = 0; b < 500; b++)
            {
                sf::Color color = layer->getImage()->getPixel(a, b);

                int red, green, blue;
                red = (0.5 * color.r);

                layer->getImage()->setPixel(a, b, sf::Color(red, color.g, color.b, 150));
            }
        }

        layer->reload();
    }

    if (button == refreshButton)
    {
        int a,b;
        for (a = 0; a < 500; a++)
        {
            for (b = 0; b < 500; b++)
            {
                sf::Color color = layer->getImage()->getPixel(a, b);

                layer->getImage()->setPixel(a, b, sf::Color(1, 1, 1, 1));
            }
        }

        layer->reload();
    }
}

