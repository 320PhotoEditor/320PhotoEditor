#pragma once

#include "Tool.h"
#include "../GUI/ButtonElement.h"
#include "ToolManager.h"

class Zoom : public Tool
{
public:

    Zoom(sf::Texture *up, sf::Texture *down, sf::Texture *over);

    void init();
    void start(Layer* layer);
    void stop() {};
    void run();

    void mouseMoved(sf::Vector2i pos);
    void zoom();

    void mousePressed(sf::Mouse::Button button);
    void buttonPressed(GUIElement* button, int status);
    sf::RenderWindow * getRenderWindow();
    sf::Vector2i getCursorPos();
    int getZoomFactor();

    //reloads the image to render
//    int update();

    ~Zoom();

private:

    int zoomFactor;
    ButtonElement* addButton;
    ButtonElement* subtractButton;

    Layer* layer;
    sf::Texture texture;
    sf::Sprite* zoomSprite;
    sf::Image* zoomImage;
    sf::Vector2i cursorPos;
    sf::RenderWindow* renderWindow;
};