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


sf::Vector2f operator/(const sf::Vector2i& a, const float& b);