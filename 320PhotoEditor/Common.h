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

sf::Vector2f operator-(const sf::Vector2i& a, const sf::Vector2f& b);

sf::Vector2f operator/(const sf::Vector2i& a, const float& b);

sf::Vector2u operator/(const sf::Vector2u& a, const int& b);

sf::Vector2i operator*(const sf::Vector2i a, const float& b);

float hue2rgb(float p, float q, float t);

//h s l range [0,1]
sf::Color hsl2rgb(float h, float s, float l);

float* rgb2hsl(sf::Color rgb);

std::string openFileDialog(sf::RenderWindow* parentWindow, bool selectMultiple = false);

typedef float Matrix3x3[3][3];