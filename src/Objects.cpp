#include <Objects.hpp>

Objects::Objects(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
{
	shape.setSize(size);
	shape.setPosition(pos);
	shape.setFillColor(color);
	shape.setOrigin(shape.getSize() / 2.f);
}

void Objects::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}