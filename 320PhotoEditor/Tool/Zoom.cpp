#include "Zoom.h"

Zoom::Zoom(sf::Texture *up, sf::Texture *down, sf::Texture *over) : Tool(up, down, over)
{
    texture = sf::Texture();
    lastCursorPos = {0, 0};
    renderWindow = nullptr;
    zoomFactor = 3;
}

void Zoom::init() {
    sf::Texture *upTexture = new sf::Texture();
    upTexture->loadFromFile("../assets/button_up.png");
    sf::Texture *downTexture = new sf::Texture();
    downTexture->loadFromFile("../assets/button_down.png");
    sf::Texture *overTexture = new sf::Texture();
    overTexture->loadFromFile("../assets/button_over.png");

    addButton = new ButtonElement(upTexture, downTexture, overTexture);
    addButton->setUpdateFunction([this](GUIElement *element, int status) { this->buttonPressed(element, status); });
    container->addElement(addButton);
    addButton->setSize({0.25, 0.25});
    addButton->setPosition({0.75, 0.75});

    subtractButton = new ButtonElement(upTexture, downTexture, overTexture);
    subtractButton->setUpdateFunction([this](GUIElement *element, int status) { this->buttonPressed(element, status); });
    container->addElement(subtractButton);
    subtractButton->setSize({0.25, 0.25});
    subtractButton->setPosition({0.5, 0.75});
}

void Zoom::start(Layer* layer)
{
    this->layer = layer;
}

void Zoom::mouseMoved(sf::Vector2i pos)
{
    cursorPos = pos;
}

int Zoom::buttonPressed(GUIElement* button, int status)
{
    if (button == addButton)
    {
        zoomFactor++;
        std::cout << zoomFactor;
        return(0);
    }

    if (button == subtractButton)
    {
        zoomFactor--;
        std::cout << zoomFactor;
        return(0);
    }
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

void Zoom::run()
{
    sf::Event event;
    if (renderWindow == nullptr) return;

    while (renderWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderWindow->close();
//            delete zoomSprite;  TODO: investigate crash...
//            delete zoomImage;
        }
    }

    renderWindow->clear();
    renderWindow->draw(*zoomSprite);
    renderWindow->display();
}

void Zoom::zoom()
{
    renderWindow = new sf::RenderWindow(sf::VideoMode(500, 500), "Zoom Window");

    zoomImage = new sf::Image();
    sf::Vector2i position = layer->cursorToPixel(cursorPos);
    sf::Rect rect(position.x - (500/(2*zoomFactor)), position.y - (500/(2*zoomFactor)), (500/zoomFactor), (500/zoomFactor));
    zoomImage->create(500, 500);
    zoomImage->copy(*layer->getImage(), 0, 0, rect);

    texture.loadFromImage(*zoomImage);
    zoomSprite = new sf::Sprite(texture);
    zoomSprite->setScale(zoomFactor, zoomFactor);
}



