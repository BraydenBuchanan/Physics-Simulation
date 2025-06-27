#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <thread>

#include <Objects.hpp>

#define SQUARE_FRICTION 2.5
#define CIRCLE_FRICTION 1.01

using namespace std::chrono_literals;


class Rigid
{
public:
	Rigid();

	void spawnSquare(sf::Vector2i pos);
	void UpdateSquare();

	void spawnCircle(sf::Vector2i pos);
	void UpdateCircle();

	void checkCollisionWithSquareToWindow(sf::RenderWindow& window);
	void checkCollisionWithCircleToWindow(sf::RenderWindow& window);
	void checkCollisionWithSquareToObjects(Objects& object, float push);
	void checkCollisionWithCircleToObjects(Objects& object, float push);
	
	void checkCollisionWithCircleToSquare();

	void setScaleCircle(sf::Vector2f scale) { circle.setScale(scale); }
	void setScaleSquare(sf::Vector2f scale) { square.setScale(scale); }

	void Draw(sf::RenderWindow& window);

	//operator bool() { return (square.getScale() == sf::Vector2f{ 1.f, 1.f }) && (circle.getScale() == sf::Vector2f{ 1.f, 1.f }); }

	bool checkScaleSquare() { return square.getScale() == sf::Vector2f{ 1.f, 1.f } ? true : false; }
	bool checkScaleCircle() { return circle.getScale() == sf::Vector2f{ 1.f, 1.f } ? true : false; }

	bool isSpawn;

public:
	sf::RectangleShape square;
	sf::CircleShape circle;

	sf::Vector2f vel;
	sf::Vector2f vel2;
private:
	float push;

	sf::Texture texture;

	const float Gravity = 0.2f;
	const float dampingFactor = -0.55f;

	const float PI = 3.14159265359f;
};

