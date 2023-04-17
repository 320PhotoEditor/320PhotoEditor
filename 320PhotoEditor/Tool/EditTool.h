#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "../Layer/LayerManager.h"

class EditTool : public Tool
{
public:

    EditTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

    void init();
    void start(Layer* layer);
    void stop() {};
    void run() {};

    void mousePressed(sf::Mouse::Button button);
    void mouseMoved(sf::Vector2i pos);
    void buttonPressed(GUIElement* button, int status);
    void hsl();

private:

    ButtonElement* hueIncButton;
    ButtonElement* hueDecButton;
    ButtonElement* satIncButton;
    ButtonElement* satDecButton;
    ButtonElement* lumIncButton;
    ButtonElement* lumDecButton;
    ButtonElement* expIncButton;
    ButtonElement* expDecButton;
    ButtonElement* completeSatIncButton;
    ButtonElement* completeSatDecButton;
    sf::Vector2i cursorPos;
    float* hslNum;
    Layer* layer;
    sf::Color color;
    bool flag;
};