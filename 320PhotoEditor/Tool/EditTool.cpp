#include "EditTool.h"


EditTool::EditTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
    flag = false;
}

void EditTool::init()
{
    sf::Texture* upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture* downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture* overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    hueIncButton = new ButtonElement(upTexture, downTexture, overTexture);
    hueIncButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(hueIncButton);
    hueIncButton->setSize({ .20, .20 });
    hueIncButton->setPosition({ 0.30, 0.10 });

    hueDecButton = new ButtonElement(upTexture, downTexture, overTexture);
    hueDecButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(hueDecButton);
    hueDecButton->setSize({ .20, .20 });
    hueDecButton->setPosition({ 0.10, 0.10 });

    satIncButton = new ButtonElement(upTexture, downTexture, overTexture);
    satIncButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(satIncButton);
    satIncButton->setSize({ .20, .20 });
    satIncButton->setPosition({ 0.30, 0.40 });

    satDecButton = new ButtonElement(upTexture, downTexture, overTexture);
    satDecButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(satDecButton);
    satDecButton->setSize({ .20, .20 });
    satDecButton->setPosition({ 0.10, 0.40 });

    lumIncButton = new ButtonElement(upTexture, downTexture, overTexture);
    lumIncButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(lumIncButton);
    lumIncButton->setSize({ .20, .20 });
    lumIncButton->setPosition({ 0.30, 0.70 });

    lumDecButton = new ButtonElement(upTexture, downTexture, overTexture);
    lumDecButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(lumDecButton);
    lumDecButton->setSize({ .20, .20 });
    lumDecButton->setPosition({ 0.10, 0.70 });

    expIncButton = new ButtonElement(upTexture, downTexture, overTexture);
    expIncButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(expIncButton);
    expIncButton->setSize({ .20, .20 });
    expIncButton->setPosition({ 0.80, 0.70 });

    expDecButton = new ButtonElement(upTexture, downTexture, overTexture);
    expDecButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(expDecButton);
    expDecButton->setSize({ .20, .20 });
    expDecButton->setPosition({ 0.60, 0.70 });

    completeSatIncButton = new ButtonElement(upTexture, downTexture, overTexture);
    completeSatIncButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(completeSatIncButton);
    completeSatIncButton->setSize({ .20, .20 });
    completeSatIncButton->setPosition({ 0.80, 0.40 });

    completeSatDecButton = new ButtonElement(upTexture, downTexture, overTexture);
    completeSatDecButton->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
    container->addElement(completeSatDecButton);
    completeSatDecButton->setSize({ .20, .20 });
    completeSatDecButton->setPosition({ 0.60, 0.40 });
}

void EditTool::start(Layer* layer)
{
    this->layer = layer;
}

void EditTool::mousePressed(sf::Mouse::Button button)
{
    if (button == sf::Mouse::Button::Left)
    {
        if (layer->isCursorOver(cursorPos))
        {
            flag = true;
            hsl();
        }
    }
}

void EditTool::mouseMoved(sf::Vector2i pos)
{
    cursorPos = pos;
}

void EditTool::hsl()
{
    sf::Vector2i position = layer->cursorToPixel(cursorPos);
    color = layer->getImage()->getPixel(position.x, position.y);

    hslNum = rgb2hsl(color);
}

void EditTool::buttonPressed(GUIElement* button, int status)
{
    if (status == ButtonElement::ButtonState::DOWN or !flag)
    {
        return;
    }

    float hueNum = hslNum[0]*360.0f;
    float hueMin = hueNum - 25.0f;
    float hueMax = hueNum + 25.0f;

    float remainderSmall = 25.0f - hueNum;
    float remainderLarge = 25.0f - (360.0f - hueNum);

    if (remainderSmall > 0.0f)
    {
        hueMin = 360.0f - remainderSmall;
    }

    if (remainderLarge > 0.0f)
    {
        hueMax = remainderLarge;
    }

    int a,b;
    for (a = 0; a < layer->getImage()->getSize().x; a++)
    {
        for (b = 0; b < layer->getImage()->getSize().y; b++)
        {
            sf::Color color2 = layer->getImage()->getPixel(a, b);
            float *hsl = rgb2hsl(color2);
            float hue = hsl[0] * 360.0f;
            float sat = hsl[1] * 100.0f;
            float lum = hsl[2] * 100.0f;

            if (button == expDecButton) {
                if (lum <= 0.0f)
                {
                    lum = 0.0f;
                }

                else lum = lum - 1.0f;
            }

            if (button == expIncButton) {
                if (lum >= 100.0f)
                {
                    lum = 100.0f;
                }

                else lum = lum + 1.0f;
            }

            if (button == completeSatDecButton) {
                if (sat <= 0.0f)
                {
                    sat = 0.0f;
                }

                else sat = sat - 1.0f;
            }

            if (button == completeSatIncButton) {
                if (sat >= 100.0f)
                {
                    sat = 100.0f;
                }

                else sat = sat + 1.0f;
            }

            if (hueMin <= hue && hue <= hueMax)
            {
                if (button == hueDecButton) {
                    if (hue <= 0.0f) {
                        hue = 360.0f;
                    }

                    hue = hue - 1.0f;
                }

                if (button == hueIncButton) {
                    if (hue >= 360.0f) {
                        hue = 0.0f;
                    }

                    hue = hue + 1.0f;
                }

                if (button == satDecButton) {
                    if (sat <= 0.0f)
                    {
                        sat = 0.0f;
                    }

                    else sat = sat - 1.0f;
                }

                if (button == satIncButton) {
                    if (sat >= 100.0f)
                    {
                        sat = 100.0f;
                    }

                    else sat = sat + 1.0f;
                }

                if (button == lumDecButton) {
                    if (lum <= 0.0f)
                    {
                        lum = 0.0f;
                    }

                    else lum = lum - 1.0f;
                }

                if (button == lumIncButton) {
                    if (lum >= 100.0f)
                    {
                        lum = 100.0f;
                    }

                    else lum = lum + 1.0f;
                }
            }

            layer->getImage()->setPixel(a, b, hsl2rgb(hue / 360.0f, sat / 100.0f, lum / 100.0f));
        }
    }

    layer->reload();
}