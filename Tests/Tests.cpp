#define BOOST_TEST_MODULE Test
#define NOMINMAX

#include <boost/test/included/unit_test.hpp>
#include "../320PhotoEditor/Common.h"
#include "../320PhotoEditor/AssetManager.h"
#include "../320PhotoEditor/ComputeShader.h"
#include "../320PhotoEditor/Common.h"

BOOST_AUTO_TEST_CASE(AssetManager_Load_From_Mem)
{
    AssetManager am = AssetManager::getInstance();

    sf::Texture* initalload = am.getTexture("../assets/button_up.png");
    sf::Texture* noload = am.getTexture("../assets/button_up.png");

    BOOST_CHECK_EQUAL(initalload, noload);
}

BOOST_AUTO_TEST_CASE(AssetManager_Load_Different)
{
    AssetManager am = AssetManager::getInstance();

    sf::Texture* initalload = am.getTexture("../assets/button_up.png");
    sf::Texture* difload = am.getTexture("../assets/button_down.png");

    BOOST_CHECK_NE(initalload, difload);
}

BOOST_AUTO_TEST_CASE(ComputeShader_Load)
{
    //create the render window to init opengl context so compute shaders will run
    sf::RenderWindow* rw = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");

    ComputeShader cs = ComputeShader("../assets/testcompute.comp");
    BOOST_CHECK_NE(cs.ID, 0);
}

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

BOOST_AUTO_TEST_CASE(RGB_To_HSL)
{
    float* h = rgb2hsl(sf::Color::Green);
    BOOST_CHECK_CLOSE(h[0], 120 / 360, 0.01);
    BOOST_CHECK_CLOSE(h[1], 1, 0.01);
    BOOST_CHECK_CLOSE(h[2], 0.5, 0.01);
}

BOOST_AUTO_TEST_CASE(HSL_To_RGB)
{
    sf::Color rgb = hsl2rgb(100 / 360, 0.5, 0.5);

    BOOST_CHECK_CLOSE((float)(rgb.r), 106.0f, 0.01);
    BOOST_CHECK_CLOSE((float)(rgb.g), 191.0f, 0.01);
    BOOST_CHECK_CLOSE((float)(rgb.b), 64.0f, 0.01);
}