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
#include "../320PhotoEditor/ComputeShader.h"
#include "../320PhotoEditor/Common.h"
#include "../320PhotoEditor/Layer/Layer.h"
#include "../320PhotoEditor/Layer/LayerManager.h"
#include "../320PhotoEditor/Tool/PaintTool.h"
#include "../320PhotoEditor/Tool/WarpTool.h"
#include "../320PhotoEditor/Tool/ToolManager.h"
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

}

//acceptance test
BOOST_AUTO_TEST_CASE(AssetManager_Texture_Load_From_Mem)
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

//acceptance test
BOOST_AUTO_TEST_CASE(AssetManager_Texture_Load_Different)
{
    AssetManager am = AssetManager::getInstance();

    sf::Texture* initalload = am.getTexture("../assets/button_up.png");
    sf::Texture* difload = am.getTexture("../assets/button_down.png");

    BOOST_CHECK_NE(initalload, difload);
}

//acceptance test
BOOST_AUTO_TEST_CASE(AssetManager_Shader_Load_From_Mem)
{
    AssetManager am = AssetManager::getInstance();

    //create the render window to init opengl context so compute shaders will run
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");

    ComputeShader* initalload = am.getComputeShader("../assets/paint_compute.comp");
    ComputeShader* noload = am.getComputeShader("../assets/paint_compute.comp");

    BOOST_CHECK_EQUAL(initalload, noload);
}

//acceptance test
BOOST_AUTO_TEST_CASE(AssetManager_Shader_Load_Different)
{
    AssetManager am = AssetManager::getInstance();

    //create the render window to init opengl context so compute shaders will run
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");

    ComputeShader* initalload = am.getComputeShader("../assets/paint_compute.comp");
    ComputeShader* difload = am.getComputeShader("../assets/select_compute.comp");

    BOOST_CHECK_NE(initalload, difload);
}

//acceptance test
BOOST_AUTO_TEST_CASE(ComputeShader_Load)
{
    //create the render window to init opengl context so compute shaders will run
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");

    ComputeShader cs = ComputeShader("../assets/testcompute.comp");
    //checks if the compute shader properly loaded and the id was set to a valid number
    BOOST_CHECK_NE(cs.ID, 0);
}

//acceptance test
BOOST_AUTO_TEST_CASE(PaintCompute_Paint)
{
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");

    ComputeShader paintCompute = ComputeShader("../assets/paint_compute.comp");

    //create an image and mask filled with white
    sf::Image texi;
    texi.create(100, 100, sf::Color::White);

    sf::Texture tex;
    tex.loadFromImage(texi);

    sf::Texture mask;
    mask.loadFromImage(texi);
    
    ComputeShader::bindTexture(tex.getNativeHandle(), 0);
    ComputeShader::bindTexture(mask.getNativeHandle(), 1);
    paintCompute.use();
    //paint a small line
    paintCompute.setVec2("firstPos", 25.0f, 25.0f);
    paintCompute.setVec2("secondPos", 30.0f, 30.0f);

    paintCompute.setFloat("paintSize", 5);
    paintCompute.setVec3("color", 0.0f, 0.0f, 0.0f);

    paintCompute.compute(100 / 10.0f, 100 / 10.0f, 1);

    //copy image back from gpu to test on
    texi = tex.copyToImage();

    //inside paint line
    BOOST_CHECK_EQUAL(texi.getPixel(25, 25).r, sf::Color::Black.r);
    BOOST_CHECK_EQUAL(texi.getPixel(25, 25).g, sf::Color::Black.g);
    BOOST_CHECK_EQUAL(texi.getPixel(25, 25).b, sf::Color::Black.b);

    //outside paint line
    BOOST_CHECK_NE(texi.getPixel(75, 75).r, sf::Color::Black.r);
    BOOST_CHECK_NE(texi.getPixel(75, 75).g, sf::Color::Black.g);
    BOOST_CHECK_NE(texi.getPixel(75, 75).b, sf::Color::Black.b);
}

//acceptance test
BOOST_AUTO_TEST_CASE(RGB_To_HSL)
{
    float* h = rgb2hsl(sf::Color::Green);
    BOOST_CHECK_CLOSE(h[0], 120 / 360, 0.01);
    BOOST_CHECK_CLOSE(h[1], 1, 0.01);
    BOOST_CHECK_CLOSE(h[2], 0.5, 0.01);
}

//acceptance test
BOOST_AUTO_TEST_CASE(HSL_To_RGB)
{
    sf::Color rgb = hsl2rgb(100 / 360, 0.5, 0.5);

    BOOST_CHECK_CLOSE((float)(rgb.r), 106.0f, 0.01);
    BOOST_CHECK_CLOSE((float)(rgb.g), 191.0f, 0.01);
    BOOST_CHECK_CLOSE((float)(rgb.b), 64.0f, 0.01);
}

//white box test
BOOST_AUTO_TEST_CASE(WarpTool_SelectPoint_Inside)
{
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1000, 1000), "window");

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    sf::Texture* texture = new sf::Texture();
    texture->loadFromImage(im);

    WarpTool* paintTool = new WarpTool(texture, texture, texture);
    paintTool->init();
    Layer* layer = new Layer({ 100, 100 }, sf::Color::White, rw);
    paintTool->start(layer);
    
    //check directly on the point
    sf::Vector2i point = paintTool->selectControlPoint({ 50, 50 });
    BOOST_CHECK_EQUAL(point.x, 1);
    BOOST_CHECK_EQUAL(point.y, 1);

    //check sligtly off
    point = paintTool->selectControlPoint({ 53, 53 });
    BOOST_CHECK_EQUAL(point.x, 1);
    BOOST_CHECK_EQUAL(point.y, 1);
}

//white box test
BOOST_AUTO_TEST_CASE(WarpTool_SelectPoint_Outside)
{
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1000, 1000), "window");

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    sf::Texture* texture = new sf::Texture();
    texture->loadFromImage(im);

    WarpTool* paintTool = new WarpTool(texture, texture, texture);
    paintTool->init();
    Layer* layer = new Layer({ 100, 100 }, sf::Color::White, rw);
    paintTool->start(layer);

    //between points 1,1 and 2,2
    sf::Vector2i point = paintTool->selectControlPoint({ 75, 75 });
    BOOST_CHECK_EQUAL(point.x, -1);
    BOOST_CHECK_EQUAL(point.y, -1);
}

//integration test, bottom-up
//tests between a Tool and ToolManager and Layer
BOOST_AUTO_TEST_CASE(Tool_ToolManager_Integration)
{
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1000, 1000), "window");

    sf::Image im = sf::Image();
    im.create(100, 100, sf::Color::White);
    sf::Texture* texture = new sf::Texture();
    texture->loadFromImage(im);

    PaintTool* paintTool = new PaintTool(texture, texture, texture);

    ToolManager* toolManager = new ToolManager(rw);
    
    Layer* layer = new Layer({100, 100}, sf::Color::White, rw);
    toolManager->setSelectedLayer(layer);

    //add the tool to the manager and select it
    toolManager->addTool(paintTool);
    toolManager->mouseMoved({ 1, 26 });
    toolManager->mousePressed(sf::Mouse::Button::Left);

    //checks if the container was set by the tool manager
    BOOST_CHECK_NE(paintTool->getContainer(), nullptr);
    //shouldn't crash if the toolManager properly initalized
    BOOST_CHECK_NO_THROW(paintTool->stop());
}

//white box test
BOOST_AUTO_TEST_CASE(Layer_cursorToPixel)
{
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1000, 1000), "window");
    
    //full window size
    Layer* layer = new Layer({ 1000, 1000 }, sf::Color::White, rw);

    sf::Vector2i p = layer->cursorToPixel({ 50, 50 });
    BOOST_CHECK_EQUAL(p.x, 50);
    BOOST_CHECK_EQUAL(p.y, 50);

    p = layer->cursorToPixel({ -50, -50 });
    BOOST_CHECK_EQUAL(p.x, -50);
    BOOST_CHECK_EQUAL(p.y, -50);

    delete layer;

    //half size the window
    layer = new Layer({ 500, 500 }, sf::Color::White, rw);

    p = layer->cursorToPixel({ 50, 50 });
    BOOST_CHECK_EQUAL(p.x, 50);
    BOOST_CHECK_EQUAL(p.y, 50);

    p = layer->cursorToPixel({ -50, -50 });
    BOOST_CHECK_EQUAL(p.x, -50);
    BOOST_CHECK_EQUAL(p.y, -50);
}
