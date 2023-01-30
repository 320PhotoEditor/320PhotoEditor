#include "Application.h"

#include <iostream>
Application::Application()
{
}

Application::~Application()
{
	delete window;
}

bool Application::init(std::string windowName)
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), windowName);

    if (!window->isOpen())
    {  
        return false;
    }

    window->setKeyRepeatEnabled(false);

    guiContainer = new GUIContainer({0, 0}, {1, 1}, window);

    sf::Texture* upTexture = new sf::Texture();
    upTexture->loadFromFile("..\\assets\\button_up.png");
    sf::Texture* downTexture = new sf::Texture();
    downTexture->loadFromFile("..\\assets\\button_down.png");
    sf::Texture* overTexture = new sf::Texture();
    overTexture->loadFromFile("..\\assets\\button_over.png");

    button = new ButtonElement(upTexture, downTexture, overTexture);
    button2 = new ButtonElement(upTexture, downTexture, overTexture);

    guiContainer->addElement(button);

    button->setSize({ 0.05, 0.05 });
    button->setPosition({ 0, 0 });

    guiContainer->addElement(button2);

    button2->setSize({ 0.05, 0.05 });
    button2->setPosition({ .05, 0 });

    guiContainer->setVisible(true);
    guiContainer->setRenderWindow(window);

    addInputListener(guiContainer);

    return true;
}

void Application::run()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            updateInputListeners(event);
        }
        window->clear();

        guiContainer->render();

        window->display();
    }
}

void Application::addInputListener(InputListener* listener)
{
    inputListeners.insert(listener);
}

void Application::removeInputListener(InputListener* listener)
{
    inputListeners.erase(listener);
}

void Application::updateInputListeners(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        for (const auto& listener : inputListeners)
        {
            listener->keyPressed(event.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        for (const auto& listener : inputListeners)
        {
            listener->keyReleased(event.key.code);
        }
        break;
    case sf::Event::MouseButtonPressed:
        for (const auto& listener : inputListeners)
        {
            listener->mousePressed(event.mouseButton.button);
        }
        break;
    case sf::Event::MouseButtonReleased:
        for (const auto& listener : inputListeners)
        {
            listener->mouseReleased(event.mouseButton.button);
        }
        break;
    case sf::Event::MouseWheelScrolled:
        for (const auto& listener : inputListeners)
        {
            listener->mouseScrolled(event.mouseWheel.delta);
        }
        break;
    case sf::Event::MouseMoved:
        for (const auto& listener : inputListeners)
        {
            listener->mouseMoved(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        }
        break;
    }
}
