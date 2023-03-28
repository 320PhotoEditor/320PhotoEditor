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
    
    this->layer = layer;
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
    }
}
