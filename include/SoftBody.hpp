#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <algorithm>

#include <Objects.hpp>
#include <RigidBodies.hpp>

#define FRICTION 0.5

inline double Magnitude(sf::Vector2f a)
{
	double magnitude = sqrt(a.x * a.x + a.y * a.y);
	return magnitude;
}

inline sf::Vector2f Unit(sf::Vector2f a)
{
	sf::Vector2f b;
	double magnitude = Magnitude(a);

	if (magnitude == 0)
		return { 0, 0 };

	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
}

inline double makeDot(sf::Vector2f a, sf::Vector2f b)
{
	double dot = a.x * b.x + a.y * b.y;
	return dot;
}

class SoftBody
{
public:
	SoftBody(float restitution, float dampingFactor, float springConst);

	void addPoint(sf::Vector2f vertex);
	void acceleratePoints();

	void checkCollisionWithWindow(sf::RenderWindow& window);
	void checkCollisionWithObjects(Objects& object, float push);
	void checkCollisionWithSquare(Rigid& rigid, float push);
	void checkCollisionWithCircle(Rigid& rigid, float push);

	void Move(float speed);

	void drawLine(sf::RenderWindow& window, sf::Vector2f a, sf::Vector2f b, sf::Color color);
	void Draw(sf::RenderWindow& window, sf::Color color);
	void clear();

	void moveForCollision(float dx, float dy)
	{
		for (int i = 0; i < softBody.size(); i++)
		{
			softBody[i].x += dx;
			softBody[i].y += dy;
		}
	}

	sf::Vector2f GetSize()
	{
		for (int i = 0; i < softBody.size(); i++)
		{
			for (int j = 0; j < softBody.size(); j++)
			{
				return softBody[i] - softBody[j];
			}
		}
	}

private:
	std::vector<sf::Vector2f> softBody;
	std::vector<sf::Vector2f> velocity;

	sf::Vector2f force;
	float springLength[200][200];

	float restitution;
	float dampingFactor;
	float springConst;

	float squarePush;
	float circlePush;

	Objects object;
};