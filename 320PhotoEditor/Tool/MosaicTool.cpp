#include "MosaicTool.h"
#include "../GUI/GUIElement.h"
#include <tchar.h>
#include <atlstr.h>
#include <windows.h>

MosaicTool::MosaicTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void MosaicTool::init()
{
}

void MosaicTool::start(Layer* layer)
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "PixelEater", sf::Style::Titlebar | sf::Style::Close);
    sf::Event listener;

    //Game loop
    while (window.isOpen())
    {
        //Event polling
        while (window.pollEvent(listener))
        {
            switch (listener.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        //update

        //render
        window.clear();

        //draw
        window.display();
    }
}

void MosaicTool::run()
{
}


void MosaicTool::buttonPressed(GUIElement* button, int status)
{
    if (status != ButtonElement::ButtonState::DOWN)
    {
        return;
    }

    if (button == selectButton)
    {
        std::cout << "Mosaic button \n";
    }
}
