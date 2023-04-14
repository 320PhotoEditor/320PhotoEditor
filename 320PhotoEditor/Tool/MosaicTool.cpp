#pragma once

#include "../game.h"

MosaicTool::MosaicTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void MosaicTool::init()
{
}

void MosaicTool::start(Layer* layer)
{
    game pixelEater;
   
    //Game loop
    while (pixelEater.running())
    {
        pixelEater.update();
        pixelEater.render();
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
