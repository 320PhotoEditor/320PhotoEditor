#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
    delete toolManager;
	delete window;
}

bool Application::init(std::string windowName)
{
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), windowName);

    if (!window->isOpen())
    {
        return false;
    }

    //TODO: clean this up, maybe have some sort of asset manager
    window->setKeyRepeatEnabled(false);

    sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
    sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
    sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

    sf::Texture* paintupTexture = AssetManager::getInstance().getTexture("../assets/paint_button_up.png");
    sf::Texture* paintdownTexture = AssetManager::getInstance().getTexture("../assets/paint_button_down.png");
    sf::Texture* paintoverTexture = AssetManager::getInstance().getTexture("../assets/paint_button_over.png");

    sf::Texture* mosUpTexture = AssetManager::getInstance().getTexture("../assets/mos_button_up.png");
    sf::Texture* mosDownTexture = AssetManager::getInstance().getTexture("../assets/mos_button_down.png");
    sf::Texture* mosOverTexture = AssetManager::getInstance().getTexture("../assets/mos_button_over.png");

    toolManager = new ToolManager(window);
    
    layerManager = new LayerManager(window, toolManager, { 800, 600 });
    layerManager->createLayer(sf::Color::White);
    
    toolManager->setSelectedLayer(layerManager->getSelectedLayer());

    applicationMenu = new ApplicationMenu(window, layerManager, toolManager);

    toolManager->setApplicationMenu(applicationMenu);

    toolManager->addTool(new TestTool(upTexture, downTexture, overTexture));
    toolManager->addTool(new PaintTool(paintupTexture, paintdownTexture, paintoverTexture));
    toolManager->addTool(new SelectTool(upTexture, downTexture, overTexture));
    toolManager->addTool(new MosaicTool(mosUpTexture, mosDownTexture, mosOverTexture));
    toolManager->addTool(new FilterTool(upTexture, downTexture, overTexture));
    toolManager->addTool(new Zoom(upTexture, downTexture, overTexture));
    toolManager->addTool(new HistogramTool(upTexture, downTexture, overTexture));

    addInputListener(applicationMenu->getMenuContainer());
    addInputListener(applicationMenu->getColorContainer());
    addInputListener(toolManager);
    addInputListener(layerManager);

    addWindowListener(applicationMenu->getMenuContainer());
    addWindowListener(applicationMenu->getColorContainer());
    addWindowListener(toolManager);

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
            {
                window->close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
            }

            updateWindowListeners(event);
            updateInputListeners(event);
        }
        window->clear();

        applicationMenu->update();
        layerManager->update();
        toolManager->update();

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

void Application::addWindowListener(WindowListener* listener)
{
    windowListeners.insert(listener);
}

void Application::removeWindowListener(WindowListener* listener)
{
    windowListeners.erase(listener);
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

void Application::updateWindowListeners(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Resized:
        for (const auto& listener : windowListeners)
        {
            listener->windowResize();
        }
        break;
    }
}
