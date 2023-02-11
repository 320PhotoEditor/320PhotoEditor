#include "Zoom.h"

Zoom::Zoom(sf::Texture *up, sf::Texture *down, sf::Texture *over) : Tool(up, down, over)
{
    texture = sf::Texture();

    sprite = new sf::Sprite(texture);
    lastCursorPos = {0, 0};
}

void Zoom::init() {
    sf::Texture *upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture *downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture *overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    color1Button = new ButtonElement(upTexture, downTexture, overTexture);
    color1Button->setUpdateFunction([this](GUIElement *element, int status) { this->buttonPressed(element, status); });
    container->addElement(color1Button);
    color1Button->setSize({0.25, 0.25});
    color1Button->setPosition({0.75, 0.75});
 }

void Zoom::start(Layer* layer)
{
    this->layer = layer;
}

void Zoom::mouseMoved(sf::Vector2i pos)
{
    cursorPos = pos;
}

void Zoom::buttonPressed(GUIElement* button, int status)
{

}

void Zoom::mousePressed(sf::Mouse::Button button)
{
    if (button == sf::Mouse::Button::Left)
    {
        if (layer->isCursorOver(cursorPos)) {
            zoom();
            lastCursorPos = cursorPos;
        }
    }
}

int Zoom::zoom()
{
    sf::RenderWindow renderWindow (sf::VideoMode(500, 500), "Zoom Window");
    layerManager = new LayerManager(&renderWindow, {500, 500});
    layerManager->createLayer(sf::Color::Blue);

    while (renderWindow.isOpen())
    {
        sf::Event event;
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderWindow.close();
            }
        }



        sf::View view(sf::FloatRect(0.f, 0.f, 500.f, 500.f));
//        view.setCenter(cursorPos.x, cursorPos.y);
//        view.setSize(100, 100);

        view.setSize(200, 200);
        renderWindow.setView(view);
        renderWindow.clear();
        layerManager->update();
        renderWindow.display();
        view.reset(sf::FloatRect(0.f, 0.f, 500.f, 500.f));
    }
}

