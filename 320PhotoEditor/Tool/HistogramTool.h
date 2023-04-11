#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "../Layer/LayerManager.h"

class HistogramTool : public Tool
{
public:
    HistogramTool(sf::Texture* up, sf::Texture* down, sf::Texture* over);

    void init();
    void start(Layer* layer);
    void stop() {};
    void run();

//void keyPressed(sf::Keyboard::Key key);
    void mousePressed(sf::Mouse::Button button);
    void buttonPressed(GUIElement* button, int status);
    void convertBW(sf::Image image);
    float* normalCDF(float *value);
    float* normalPDF(float *histData);

private:

    Layer* layer;
    ButtonElement* bwButton;
    ButtonElement* eqButton;
    sf::Image* histImage;
    float arrays[256] = {};
};