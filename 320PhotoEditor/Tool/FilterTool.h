#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "../Layer/LayerManager.h"

class FilterTool : public Tool
{
public:

    FilterTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

    void init();
    void start(Layer* layer);
    void stop() {};
    void run() {};

    void mousePressed(sf::Mouse::Button button);
    void buttonPressed(GUIElement* button, int status);

private:

    ButtonElement* bwButton;
    ButtonElement* orangeButton;
    ButtonElement* refreshButton;
//    sf::Vector2i cursorPos;
    Layer* layer;
};