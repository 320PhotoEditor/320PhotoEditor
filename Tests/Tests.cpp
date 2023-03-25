#define BOOST_TEST_MODULE Tests
#define NOMINMAX
#include <boost/test/included/unit_test.hpp>
#include "../320PhotoEditor/Common.h"
#include "../320PhotoEditor/AssetManager.h"
#include "../320PhotoEditor/GUI/GUIContainer.h"
#include "../320PhotoEditor/GUI/GUIElement.h"
#include "../320PhotoEditor/GUI/ButtonElement.h"



BOOST_AUTO_TEST_SUITE(GUIElementTestSuite)

// Big bang integration test
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

// Big bang integration test
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

// Big bang integration test
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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GUIContainerTestSuite)

// Acceptance test
BOOST_AUTO_TEST_CASE(Container_element_set_pos)
{
	sf::Vector2f con_pos = { 1, 1 };
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer(con_pos, { 0.5, 0.5 }, window, false);

	sf::Vector2f pos = container->getPosition();

	BOOST_CHECK_EQUAL(pos.y, con_pos.y);
	BOOST_CHECK_EQUAL(pos.x, con_pos.x);
}

// Acceptance test
BOOST_AUTO_TEST_CASE(Container_element_reset_pos)
{
	sf::Vector2f init_con_pos = { 0, 0 };
	sf::Vector2f reset_con_pos = { 10, 10 };
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer(init_con_pos, { 0.5, 0.5 }, window, false);

	container->setPosition(reset_con_pos);
	sf::Vector2f pos = container->getPosition();

	BOOST_CHECK_EQUAL(pos.y, reset_con_pos.y);
	BOOST_CHECK_EQUAL(pos.x, reset_con_pos.x);
}

// Acceptance test
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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ButtonElementTestSuite)

// Big bang integration test
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
	button->setPosition({ 1, 1 });
	button->setPosition({ 5, 5 });

	sf::Vector2f pos = button->getPosition();

	BOOST_CHECK_EQUAL(pos.y, 5);
	BOOST_CHECK_EQUAL(pos.x, 5);
}

// Big bang integration test
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
	button->setPosition({ 1, 1 });

	sf::Vector2f pos = button->getPosition();

	BOOST_CHECK_EQUAL( pos.y, 1);
	BOOST_CHECK_EQUAL( pos.x, 1);
}

// Big bang integration test
BOOST_AUTO_TEST_CASE(button_element_default_set_pos)
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

// Big bang integration test
BOOST_AUTO_TEST_CASE(button_element_default_pos_no_overlap)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button1 = new ButtonElement(upTexture, downTexture, overTexture);
	ButtonElement* button2 = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button1);
	button1->setSize({ 0.1, 0.1 });
	container->addElement(button2);
	button2->setSize({ 0.1, 0.1 });

	sf::Vector2f pos1 = button1->getPosition();
	sf::Vector2f pos2 = button2->getPosition();

	BOOST_CHECK_EQUAL(pos1.y, pos2.y);
	BOOST_CHECK_NE(pos1.x, pos2.x);
}


/*
	ButtonElement mousePressed() whitebox test with 100% branch coverage over the
	next three tests.

void ButtonElement::mousePressed(sf::Mouse::Button button)
{
	if (isCursorOver(cursorPos))
	{
		if (toggle)
		{
			if (buttonState == DOWN)
			{
				sprite->setTexture(*up); //PRIVATE
				buttonState = UP; //PRIVATE
				updateFunc(this, UP);
			}
			else
			{
				sprite->setTexture(*down); //PRIVATE
				buttonState = DOWN;  //PRIVATE
				updateFunc(this, DOWN);
			}
		}
		else
		{
			sprite->setTexture(*down); //PRIVATE
			buttonState = DOWN; //PRIVATE
			updateFunc(this, DOWN);
		}
	}
}
*/

BOOST_AUTO_TEST_CASE(button_element_mouse_pressed_TTT_TTF)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");
	
	bool* test = new bool(false);

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture, true);
	container->addElement(button);
	button->setSize({ 0.1,0.1 });
	button->setPosition({ 0,0 });
	button->setUpdateFunction([test](GUIElement* element, int status) { *test = !(*test); });
	container->mouseMoved({ 5, 5 });
	
	button->mousePressed(sf::Mouse::Left);

	BOOST_CHECK_EQUAL(*test, true);

	button->mousePressed(sf::Mouse::Left);

	BOOST_CHECK_EQUAL(*test, false);
}

BOOST_AUTO_TEST_CASE(button_element_mouse_pressed_TF)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");
	
	bool* test = new bool(false);

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1,0.1 });
	button->setPosition({ 0,0 });
	button->setUpdateFunction([test](GUIElement* element, int status) { *test = !(*test); });
	container->mouseMoved({ 5, 5 });
	
	button->mousePressed(sf::Mouse::Left);

	BOOST_CHECK_EQUAL(*test, true);
}

BOOST_AUTO_TEST_CASE(button_element_mouse_pressed_F)
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	bool* test = new bool(false);

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(100, 100), "TestWindow");
	GUIContainer* container = new GUIContainer({ 0, 0 }, { 1, 1 }, window, false);
	ButtonElement* button = new ButtonElement(upTexture, downTexture, overTexture);
	container->addElement(button);
	button->setSize({ 0.1,0.1 });
	button->setPosition({ 0,0 });
	button->setUpdateFunction([test](GUIElement* element, int status) { *test = !(*test); });
	container->mouseMoved({ 50, 50 });

	button->mousePressed(sf::Mouse::Left);

	BOOST_CHECK_EQUAL(*test, false);
}

BOOST_AUTO_TEST_SUITE_END()