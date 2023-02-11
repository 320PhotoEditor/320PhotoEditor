#pragma once

#include "Tool.h"
#include "GUI/ButtonElement.h"
#include "Layer/LayerManager.h"
#include "ToolManager.h"
#include "InputListener.h"
#include "Application.h"

class Zoom : public Tool
{
public:

    Zoom(sf::Texture *up, sf::Texture *down, sf::Texture *over);

    void init();
    void start(Layer* layer);
    void stop() {};
    void run() {};
    bool isCursorOver(sf::Vector2i cursorPos);
    void mouseMoved(sf::Vector2i pos);
    int zoom();

    void mousePressed(sf::Mouse::Button button);
    void buttonPressed(GUIElement* button, int status);

    //reloads the image to render
    void reload();

    ~Zoom();

private:

    ButtonElement* color1Button;

    sf::Texture texture;
    sf::Sprite* sprite;
    sf::Image* image;
    sf::Vector2i cursorPos;
    sf::Vector2i lastCursorPos;

    Layer* layer;
    LayerManager* layerManager;
};