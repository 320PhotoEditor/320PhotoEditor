#include "Common.h"

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f operator*=(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a * b);
}

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2u& b)
{
	return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2u& b)
{
	return sf::Vector2f(a.x / b.x, a.y / b.y);
}

sf::Vector2f operator/(const sf::Vector2i& a, const sf::Vector2u& b)
{
	return sf::Vector2f((float)a.x / (float)b.x, (float)a.y / (float)b.y);
}