#include "HistogramTool.h"


HistogramTool::HistogramTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void HistogramTool::init()
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
}

void HistogramTool::start(Layer* layer)
{
    this->layer = layer;
    histImage = new sf::Image();
}

void HistogramTool::run()
{

}

void HistogramTool::mousePressed(sf::Mouse::Button button)
{

}


void HistogramTool::buttonPressed(GUIElement* button, int status)
{
    if (status == ButtonElement::ButtonState::DOWN)
    {
        return;
    }

    if (button == bwButton)
    {
        int a, b;
        float max_element = 0;
        float arrays[256] = {};

        histImage->create(256, 256, sf::Color::Black);

        for (a = 0; a < layer->getImage()->getSize().x; a++) {
            for (b = 0; b < layer->getImage()->getSize().y; b++) {
                sf::Color color2 = layer->getImage()->getPixel(a, b);
                int grayscale = ((color2.r * 0.3) + (color2.g * 0.59) + (color2.b * 0.11));
                arrays[grayscale - 1] += 1;

                if (arrays[grayscale - 1] > max_element)
                {
                    max_element = arrays[grayscale - 1];
                }
            }
        }

        float scale_factor = 256 / max_element;

        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                if ((arrays[i] * scale_factor) >= j) {
                    histImage->setPixel(i, 256 - j, sf::Color::Red);
                }
            }
        }

        applicationMenu->histTexture->loadFromImage(*histImage);

    }
}

void HistogramTool::convertBW(sf::Image image)
{

}






























