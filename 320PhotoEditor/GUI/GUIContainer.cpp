#include "GUIContainer.h"

GUIContainer::GUIContainer(sf::Vector2f pos, sf::Vector2f size, sf::RenderWindow* renderWindow, bool rightAnchor)
{
    this->size = size;
    this->renderWindow = renderWindow;
    this->rightAnchor = rightAnchor;
    setPosition(pos);
    visible = true;
    cursorPos = sf::Vector2i(0, 0);
}

sf::Vector2f GUIContainer::getPosition()
{
    return pos;
}

void GUIContainer::setPosition(sf::Vector2f pos)
{
    if (rightAnchor)
    {
        float aspect = (float)renderWindow->getSize().x / (float)renderWindow->getSize().y;
        this->pos = { aspect - pos.x - size.x, pos.y };
    }
    else
    {
        this->pos = pos;
    }
}

sf::Vector2f GUIContainer::getSize()
{
    return size;
}

void GUIContainer::setSize(sf::Vector2f size)
{
    this->size = size;
}

void GUIContainer::addElement(GUIElement* element)
{
    elements.insert(element);
    element->setContainer(this);
}

void GUIContainer::removeElement(GUIElement* element)
{
    elements.erase(element);
}

void GUIContainer::render()
{
    if (visible)
    {
        for (const auto& element : elements)
        {
            element->_render();
        }
    }
}

void GUIContainer::setVisible(bool visible)
{
    for (const auto& element : elements)
    {
        element->setVisible(visible);
    }
}

sf::RenderWindow* GUIContainer::getRenderWindow()
{
    return renderWindow;
}

void GUIContainer::setRenderWindow(sf::RenderWindow* renderWindow)
{
    this->renderWindow = renderWindow;
}

void GUIContainer::mousePressed(sf::Mouse::Button button)
{
    if (isCursorOver(cursorPos))
    {
        for (const auto& element : elements)
        {
            element->mousePressed(button);
        }
    }
}

void GUIContainer::mouseReleased(sf::Mouse::Button button)
{
    if (isCursorOver(cursorPos))
    {
        for (const auto& element : elements)
        {
            element->mouseReleased(button);
        }
    }
}

void GUIContainer::mouseMoved(sf::Vector2i pos)
{
    cursorPos = pos;

    for (const auto& element : elements)
    {
        element->mouseMoved(pos);
    }
}

bool GUIContainer::isCursorOver(sf::Vector2i cursorPos)
{
    sf::Vector2u windowSize = renderWindow->getSize();
    sf::Vector2f cPos = cursorPos / windowSize;
    float aspect = (float)windowSize.x / (float)windowSize.y;
    cPos.x *= aspect;

    float left = pos.x;
    float right = pos.x + size.x;
    float top = pos.y;
    float bottom = pos.y + size.y;

    return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}
