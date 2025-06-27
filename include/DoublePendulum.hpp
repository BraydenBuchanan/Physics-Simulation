#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class DoublePendulum
{
public:
	DoublePendulum(int mass, int length, int x, int y);
	DoublePendulum(int mass, int length, DoublePendulum* lowerPendulum);

	void Update(sf::Vector2i pos);
	void dragPendulum(sf::Vector2i pos);

	bool isMouseClickedOnBob(sf::Vector2i pos);
	bool isDragPendulum(sf::Vector2i pos);

	int getXPoint() { return arm.getPosition().x - length * sin(Theta); }
	int getYPoint() { return arm.getPosition().y + length * cos(Theta); }

	void setScale(sf::Vector2f scale);
	void setVelocity(float velocity) { aVel = velocity, lowerPendulum->aVel = velocity; }

	void Draw(sf::RenderWindow& window);
private:
	const float PI = 3.14159265359f;
	const float Gravity = 0.098f;
	const float dampingFactor = 0.9995f;

	int mass, length, x, y;
	float aAcel, aVel, Theta;

	bool dragEnable;
	bool dragDisable;

	DoublePendulum* lowerPendulum;

	sf::RectangleShape arm;
	sf::CircleShape bob;
};