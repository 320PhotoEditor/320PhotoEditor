#include "TestTool.h"
#include "Application.h"

TestTool::TestTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void TestTool::start(Layer* layer)
{
	this->layer = layer;
}

void TestTool::keyPressed(sf::Keyboard::Key key)
{
	layer->getImage()->setPixel(0, 0, sf::Color::Red); 
	layer->reload();
}

void TestTool::mousePressed(sf::Mouse::Button button)
{
    sf::RenderWindow newWindow(sf::VideoMode(500, 500), "Zoom Window");

    while (newWindow.isOpen())
    {
        sf::Event event;
        while (newWindow.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    newWindow.close();
                    break;

                //if (event.type == sf::Event::MouseButtonPressed)
                //{
                case sf::Event::MouseEntered:
                    if (event.type == sf::Event::MouseButtonPressed) {
                        newWindow.close();
                    }
                    break;
            }

        }
    }
}