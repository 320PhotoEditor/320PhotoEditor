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
#include "../320PhotoEditor/GUI/HistogramElement.h"
#include <filesystem>
#include <iostream>
#include <string>


// Acceptance Test
// When one of the Zoom Factor Buttons is pressed, the zoom factor should change
// Keeps track of teh Zoom Factor before and after the button is pressed
BOOST_AUTO_TEST_CASE(Zoom_Factor_Check)
{
    sf::Texture* upTexture = new sf::Texture();

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    upTexture->loadFromImage(im);


    sf::RenderWindow *renderWindow = new sf::RenderWindow(sf::VideoMode(1000, 1000), "windowName");
    Layer *layer = new Layer({1, 1}, sf::Color::Black, renderWindow);
    Zoom *zoomTool = new Zoom(upTexture, upTexture, upTexture);


    GUIContainer *menuContainer = new GUIContainer({ 0, 0 }, { 1, 1 }, renderWindow);
    zoomTool->setContainer(menuContainer);

    zoomTool->init();
    zoomTool->start(layer);

    int before = zoomTool->getZoomFactor();

    menuContainer->mouseMoved({251, 251});
    menuContainer->mousePressed(sf::Mouse::Button::Left);
    int after = zoomTool->getZoomFactor();

    BOOST_CHECK_NE(before, after);
}


// Acceptance Test
// When the Zoom Menu is activated, and the user clicks on the layer, a new Window should appear
// Verifies that the window is opened after the user clicks on the layer
BOOST_AUTO_TEST_CASE(Zoom_Window_Check)
{
    sf::Texture* upTexture = new sf::Texture();

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    upTexture->loadFromImage(im);


    sf::RenderWindow *renderWindow = new sf::RenderWindow(sf::VideoMode(1000, 750), "windowName");
    Layer *layer = new Layer({750, 750}, sf::Color::Black, renderWindow);
    Zoom *zoomTool = new Zoom(upTexture, upTexture, upTexture);

    GUIContainer *menuContainer = new GUIContainer({ 0, 0 }, { 1, 1 }, renderWindow);
    zoomTool->setContainer(menuContainer);

    zoomTool->init();
    zoomTool->start(layer);

    zoomTool->mouseMoved({500, 500});
    zoomTool->mousePressed(sf::Mouse::Button::Left);
    zoomTool->getRenderWindow();

    BOOST_CHECK(zoomTool->getRenderWindow()->isOpen());
}


// Acceptance Test
// Check to make sure the MouseMoved feature works...
// keeps track of the x,y coordinates of the mouse
BOOST_AUTO_TEST_CASE(LayerManager_MouseMoved)
{
    sf::Texture* upTexture = new sf::Texture();

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    upTexture->loadFromImage(im);


    sf::RenderWindow *renderWindow = new sf::RenderWindow(sf::VideoMode(1000, 750), "windowName");
    Layer *layer = new Layer({750, 750}, sf::Color::Black, renderWindow);
    GUIContainer *menuContainer = new GUIContainer({ 0, 0 }, { 1, 1 }, renderWindow);
    Zoom *zoomTool = new Zoom(upTexture, upTexture, upTexture);

    zoomTool->setContainer(menuContainer);
    zoomTool->init();
    zoomTool->start(layer);

    zoomTool->mouseMoved({500, 500});
    sf::Vector2i before = zoomTool->getCursorPos();
    layer->cursorToPixel(before);


    zoomTool->mouseMoved({600, 600});
    sf::Vector2i after = zoomTool->getCursorPos();
    layer->cursorToPixel(after);

    BOOST_CHECK_NE(before.x, after.x);
}


// Acceptance Test
// When the BW Filter button is pressed it changes the RGB values of the image
// Checks the value of a pixel before and after the BW Filter button is pressed
BOOST_AUTO_TEST_CASE(FilterTool_BW_Filter)
{
    sf::Texture* upTexture = new sf::Texture();

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    upTexture->loadFromImage(im);


    sf::RenderWindow *renderWindow = new sf::RenderWindow(sf::VideoMode(1000, 1000), "windowName");
    Layer *layer = new Layer({100, 100}, sf::Color::Red, renderWindow);
    GUIContainer *menuContainer = new GUIContainer({ 0, 0 }, { 1, 1 }, renderWindow);
    FilterTool *filterTool = new FilterTool(upTexture, upTexture, upTexture);

    filterTool->setContainer(menuContainer);
    filterTool->init();
    filterTool->start(layer);


    sf::Color color1 = layer->getImage()->getPixel(2, 2);
    int beforeRed = color1.r;

    menuContainer->mouseMoved({251, 751});
    menuContainer->mousePressed(sf::Mouse::Button::Left);

    sf::Color color2 = layer->getImage()->getPixel(2,2);
    int afterRed = color2.r;

    BOOST_CHECK_NE(beforeRed, afterRed);
}


// Acceptance Test
// Code isn't finished... Checks if the image has been converted to grayscale from color
BOOST_AUTO_TEST_CASE(Histogram_Element_toGrayscale)
{
    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    HistogramElement histElem;

    BOOST_CHECK_NE(histElem.toGrayscale(&im)->getPixel(0,0).r, 255);
}


// Acceptance Test
// Code isn't finished... Checks if the image has been converted from grayscale to color
BOOST_AUTO_TEST_CASE(Histogram_Element_toColor)
{
    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    HistogramElement histElem;

    BOOST_CHECK_NE(histElem.toColor(&im)->getPixel(0,0).r, 255);
}

// Acceptance Test
// Code isn't finished... Calculates the values for the histogram
// Takes an image and returns a vector... checks if the vector is larger than 0... i.e has been created
BOOST_AUTO_TEST_CASE(Histogram_Element_CalcHistogram)
{
    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    HistogramElement histElem;

    BOOST_CHECK_GT(histElem.calcHistogram(&im).size(), 0);
}


// Acceptance Test
// Code isn't finished... Returns a calibrated Histogram Image
// Checks if the values of the histogram have been changed
BOOST_AUTO_TEST_CASE(Histogram_Element_normalizeHistogram)
{
    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    HistogramElement histElem;

    BOOST_CHECK_NE(histElem.normalizeHistogram(&im), &im);
}


// Acceptance Test
// Code isn't finished... Takes in a vector and returns a histogram image
// Takes a vector and creates a histogram Image... checks if the Image has been created
BOOST_AUTO_TEST_CASE(Histogram_Element_createHistogram)
{
    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    HistogramElement histElem;
    std::vector<float> vect;

    BOOST_CHECK_NE(histElem.createHistogram(vect), &im);
}


// Acceptance Test
// Code isn't finished... Takes in a histogram image and computes the cumulative distribution
// and returns the new histogram image
// Checks if the image has been changed after cumulativeDistribution()
BOOST_AUTO_TEST_CASE(Histogram_Element_cumulativeDistribution)
{
    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::Red);
    HistogramElement histElem;

    BOOST_CHECK_NE(histElem.cumulativeDistribution(&im), &im);
}