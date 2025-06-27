#pragma once
#include <SFML/Graphics.hpp>

class Objects
{
public:
	Objects() = default;
	Objects(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
	
	const sf::Vector2f GetSize() { return shape.getSize(); }
	const sf::Vector2f GetPosition() { return shape.getPosition(); }

	void setColor(sf::Color color) { shape.setFillColor(color); }
	void setScale(sf::Vector2f factor) { shape.setScale(factor.x, factor.y); }

	operator bool() { return shape.getScale() == sf::Vector2f{ 1.f, 1.f }; }

	void move(float dx, float dy) { shape.move(dx, dy); }
	void Draw(sf::RenderWindow& window);

	sf::RectangleShape shape;
};