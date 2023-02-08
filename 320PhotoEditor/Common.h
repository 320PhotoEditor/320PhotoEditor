#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>
#include <functional>

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2f& b);
sf::Vector2f operator*=(const sf::Vector2f& a, const sf::Vector2f& b);

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2u& b);
sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2u& b);

sf::Vector2f operator/(const sf::Vector2i& a, const sf::Vector2u& b);

sf::Vector2f operator/(const sf::Vector2u& a, const sf::Vector2u& b);

sf::Vector2f operator/(const sf::Vector2i& a, const float& b);

sf::Vector2u operator/(const sf::Vector2u& a, const int& b);

sf::Vector2i operator*(const sf::Vector2i a, const float& b);