#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pendulum
{
public:
	Pendulum(int mass, int l, int x, int y);

	void Update(sf::Vector2i pos);
	void dragPendulum(sf::Vector2i pos);
	
	bool isMouseClickedOnBob(sf::Vector2i pos);
	bool isDragPendulum(sf::Vector2i pos);
	
	int getXPoint() { return arm.getPosition().x - l * sin(Theta); }
	int getYPoint() { return arm.getPosition().y + l * cos(Theta); }

	void setScale(sf::Vector2f scale);

	void Draw(sf::RenderWindow& window);
private:
	const float PI = 3.14159265359f;
	const float Gravity = 0.098f;
	const float dampingFactor = 0.9995f;

	bool dragEnable;
	bool dragDisable;

	int mass, x, y, l;
	float aAcel, aVel, Theta;

	sf::RectangleShape arm;
	sf::CircleShape bob;
};