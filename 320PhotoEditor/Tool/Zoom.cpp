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

sf::Image* Zoom::getImage()
{
    return image;
}

sf::Sprite* Zoom::getSprite()
{
    return sprite;
}

sf::Vector2i Zoom::cursorToPixel(sf::Vector2i cursorPos)
{
    //TODO: make adjust for image scale and position
    return sf::Vector2i(cursorPos.x - sprite->getPosition().x, cursorPos.y - sprite->getPosition().y);
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
    if (layer->isCursorOver(cursorPos))
    {
        zoom();
    }
}

int Zoom::zoom()
{

    Application application;

    sf::RenderWindow renderWindow (sf::VideoMode(500, 500), "Zoom Window");
    layerManager = new LayerManager(&renderWindow, {500, 500});
    layerManager->createLayer(sf::Color::Blue);
    //toolManager->setSelectedLayer(layerManager->getSelectedLayer());

//    layer->getImage();
//    layer->reload();
    //    renderWindow.display();

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

        renderWindow.clear();
        layerManager->update();
        renderWindow.display();
    }

    if (!application.init("Test"))
    {
        return EXIT_FAILURE;
    }

    application.run();
}

