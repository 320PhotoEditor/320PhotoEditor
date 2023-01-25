#pragma once

#include "../Common.h"
#include "../InputListener.h"
#include "GUIElement.h"

class GUIElement;

//an invisible container for GUIElements
class GUIContainer : public InputListener
{
public:

	GUIContainer(sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow* renderWindow);

	//converts pixel coords to screen coords with the range being 0-1 on y-axis and 0-aspect ratio on x-axis
	sf::Vector2f pixelToScreen(sf::Vector2i pixel);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	sf::Vector2f getScale();
	void setScale(sf::Vector2f scale);

	void addElement(GUIElement* element);
	void removeElement(GUIElement* element);

	void render();

	void setVisible(bool visible);

	sf::RenderWindow* getRenderWindow();
	void setRenderWindow(sf::RenderWindow* renderWindow);

private:

	void mousePressed(sf::Mouse::Button button);
	void mouseReleased(sf::Mouse::Button button);
	void mouseMoved(sf::Vector2i pos);

	bool isCursorOver(sf::Vector2i cursorPos);

	sf::Vector2i cursorPos;

	sf::RenderWindow* renderWindow;
	bool visible;

	sf::Vector2f pos;
	sf::Vector2f scale;

	std::set<GUIElement*> elements;

};
