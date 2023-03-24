#define BOOST_TEST_MODULE Test
#define NOMINMAX
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "../320PhotoEditor/Common.h"
#include "../320PhotoEditor/AssetManager.h"
#include "../320PhotoEditor/GUI/GUIContainer.h"
#include "../320PhotoEditor/GUI/ButtonElement.h"
#include "../320PhotoEditor/ApplicationMenu.h"
#include "../320PhotoEditor/Tool/Zoom.h"
#include "../320PhotoEditor/Application.h"
#include "../320PhotoEditor/Tool/Tool.h"
#include "../320PhotoEditor/Tool/ToolManager.h"
#include <filesystem>
#include <iostream>
#include <string>


BOOST_AUTO_TEST_CASE(Zoom_Window_Check)
{
    sf::Texture* upTexture = new sf::Texture();

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    upTexture->loadFromImage(im);


    sf::RenderWindow *renderWindow = new sf::RenderWindow(sf::VideoMode(1000, 750), "windowName");
    Layer *layer = new Layer({750, 500}, sf::Color::Black, renderWindow);
    Zoom *zoomTool = new Zoom(upTexture, upTexture, upTexture);

    GUIContainer *menuContainer = new GUIContainer({ 0, 0 }, { 1, 1 }, renderWindow);
    zoomTool->setContainer(menuContainer);

    zoomTool->init();
    zoomTool->start(layer);

    zoomTool->mouseMoved({500, 500});
    zoomTool->getRenderWindow();

    BOOST_CHECK(zoomTool->getRenderWindow()->isOpen());

}








