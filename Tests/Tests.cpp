#define BOOST_TEST_MODULE Tests
#define NOMINMAX
#include <boost/test/included/unit_test.hpp>
#include "../320PhotoEditor/Common.h"
#include "../320PhotoEditor/AssetManager.h"
#include "../320PhotoEditor/GUI/GUIContainer.h"
#include "../320PhotoEditor/GUI/GUIElement.h"
#include "../320PhotoEditor/GUI/ButtonElement.h"



BOOST_AUTO_TEST_SUITE(GUIElementTestSuite)
/*
bool GUIElement::isCursorOver(sf::Vector2i cursorPos)
{
	sf::Vector2f containerPos = container->getPosition();
	sf::Vector2f containerSize = container->getSize();
	float windowSize = container->getRenderWindow()->getSize().y;

	sf::Vector2f cPos = cursorPos / windowSize;

	float left = (pos.x * containerSize.x) + containerPos.x;
	float right = ((pos.x + size.x) * containerSize.x) + containerPos.x;
	float top = (pos.y * containerSize.y) + containerPos.y;
	float bottom = ((pos.y + size.y) * containerSize.y) + containerPos.y;

	return cPos.x >= left && cPos.x <= right && cPos.y >= top && cPos.y <= bottom;
}
*/

BOOST_AUTO_TEST_CASE(cursor_within_GUI_element)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1,0.1 });
	button->setPosition({ 0,0 });

	bool isover = button->isCursorOver({ 5,5 });

	BOOST_CHECK_EQUAL(true, isover);
}

BOOST_AUTO_TEST_CASE(cursor_outside_GUI_element)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1,0.1 });
	button->setPosition({ 0,0 });

	bool isover = button->isCursorOver({ 50, 50 });

	BOOST_CHECK_EQUAL(false, isover);
}

BOOST_AUTO_TEST_CASE(cursor_edge_GUI_element)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1,0.1 });
	button->setPosition({ 0,0 });

	bool isover = button->isCursorOver({ 10,10 });

	BOOST_CHECK_EQUAL(true, isover);
}



BOOST_AUTO_TEST_CASE(Container_element_pos)
{
	sf::Vector2f con_pos = { 0, 0 };
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer(con_pos, { 0.5, 0.5 }, window, false);

	sf::Vector2f pos = container->getPosition();

	BOOST_CHECK_EQUAL(pos.y, con_pos.y);
	BOOST_CHECK_EQUAL(pos.x, con_pos.x);
}

BOOST_AUTO_TEST_CASE(Container_element_pos_actual)
{
	sf::Vector2f con_assigned_pos = { 100, 100 };
	sf::Vector2f con_expected_pos = { 50, 50 };
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer(con_assigned_pos, { 0.5, 0.5 }, window, false);

	sf::Vector2f pos = container->getPosition();

	BOOST_CHECK_EQUAL(pos.y, con_expected_pos.y);
	BOOST_CHECK_EQUAL(pos.x, con_expected_pos.x);
}

BOOST_AUTO_TEST_CASE(button_element_reset_pos)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1, 0.1 });
	button->setPosition({ 0, 0 });
	button->setPosition({ 5, 5 });

	sf::Vector2f pos = button->getPosition();

	BOOST_CHECK_EQUAL(pos.y, 5);
	BOOST_CHECK_EQUAL(pos.x, 5);
}

BOOST_AUTO_TEST_CASE(button_element_set_pos)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1, 0.1 });
	button->setPosition({ 0, 0 });

	sf::Vector2f pos = button->getPosition();

	BOOST_CHECK_EQUAL( pos.y, 0);
	BOOST_CHECK_EQUAL( pos.x, 0);
}

BOOST_AUTO_TEST_CASE(button_element_no_set_pos)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1, 0.1 });

	sf::Vector2f pos = button->getPosition();

	BOOST_CHECK_EQUAL(pos.y, 0);
	BOOST_CHECK_EQUAL(pos.x, 0);
}

BOOST_AUTO_TEST_SUITE_END()