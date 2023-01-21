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
	window = new sf::RenderWindow(sf::VideoMode(800, 600), windowName);

    if (!window->isOpen())
    {  
        return false;
    }

    guiContainer = new GUIContainer({0, 0}, {1, 1}, window);

    guiContainer->addElement(new ButtonElement(guiContainer, "../assets/button_up.png", "../assets/button_down.png", "../assets/button_over.png", {0, 0}, {.1, .1}));

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
    case sf::Event::KeyReleased:
        for (const auto& listener : inputListeners)
        {
            listener->keyReleased(event.key.code);
        }
    case sf::Event::MouseButtonPressed:
        for (const auto& listener : inputListeners)
        {
            listener->mousePressed(event.mouseButton.button);
        }
    case sf::Event::MouseButtonReleased:
        for (const auto& listener : inputListeners)
        {
            listener->mouseReleased(event.mouseButton.button);
        }
    case sf::Event::MouseWheelScrolled:
        for (const auto& listener : inputListeners)
        {
            listener->mouseScrolled(event.mouseWheel.delta);
        }
    case sf::Event::MouseMoved:
        for (const auto& listener : inputListeners)
        {
            listener->mouseMoved(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        }
    }
}