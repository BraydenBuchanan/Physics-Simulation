#include <RigidBodies.hpp>

Rigid::Rigid() : isSpawn(true)
{
}

void Rigid::spawnSquare(sf::Vector2i pos)
{
	srand(time(nullptr));
	bool choice = rand() % 2;

	if (isSpawn)
	{
		isSpawn = false;

		vel.x = 0.f, vel.y = 0.f;

		if (choice)
			vel.x -= vel.x + atan(rand() % 10);
		else
			vel.x += vel.x + atan(rand() % 10);

		square.setSize(sf::Vector2f(65.f, 65.f));
		square.setFillColor(sf::Color(255, 165, 0));
		square.setPosition(pos.x, pos.y);
		square.setOrigin(square.getSize() / 2.f);
	}
}

void Rigid::spawnCircle(sf::Vector2i pos)
{
	srand(time(nullptr));
	bool choice = rand() % 2;

	if (isSpawn)
	{
		isSpawn = false;

		vel2.x = 0.f, vel2.y = 0.f;

		if (choice)
			vel2.x -= vel2.x + atan(rand() % 10);
		else
			vel2.x += vel2.x + atan(rand() % 10);

		circle.setRadius(32.5f);
		circle.setFillColor(sf::Color(255, 165, 0));
		circle.setPosition(pos.x, pos.y);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
	}
}

void Rigid::UpdateSquare()
{
	vel.y += Gravity;
	square.move(vel);
}

void Rigid::UpdateCircle()
{
	vel2.y += Gravity;
	circle.move(vel2);
}

void Rigid::checkCollisionWithSquareToWindow(sf::RenderWindow& window)
{
	if (square.getPosition().y + square.getSize().y / 2.f >= window.getSize().y || square.getPosition().y <= 0.f)
	{
		square.setPosition(square.getPosition().x, square.getPosition().y <= 0.f ? 0.f : window.getSize().y - square.getSize().y / 2.f);
		isSpawn = true;

		vel.y *= dampingFactor;
		vel.x /= SQUARE_FRICTION;
	}

	if (square.getPosition().x + square.getSize().x / 2 >= window.getSize().x || square.getPosition().x <= 0.f)
	{
		square.setPosition(square.getPosition().x <= 0.f ? 0.f : window.getSize().x - square.getSize().x / 2.f, square.getPosition().y);
		isSpawn = true;

		vel.x *= dampingFactor;
		vel.x /= SQUARE_FRICTION;
	}
}

void Rigid::checkCollisionWithCircleToWindow(sf::RenderWindow& window)
{
	if (circle.getPosition().y + circle.getRadius() >= window.getSize().y || circle.getPosition().y <= 0.f)
	{
		circle.setPosition(circle.getPosition().x, circle.getPosition().y <= 0.f ? 0.f : window.getSize().y - circle.getRadius());
		isSpawn = true;

		vel2.y *= dampingFactor;
		vel2.x /= CIRCLE_FRICTION;
	}

	if (circle.getPosition().x + circle.getRadius() >= window.getSize().x || circle.getPosition().x <= 0.f)
	{
		circle.setPosition(circle.getPosition().x <= 0.f ? 0.f : window.getSize().x - circle.getRadius(), circle.getPosition().y);
		isSpawn = true;

		vel2.x *= dampingFactor;
		vel2.x /= CIRCLE_FRICTION;
	}
}

void Rigid::checkCollisionWithSquareToObjects(Objects& object, float push)
{
	sf::Vector2f objectPos = object.GetPosition();
	sf::Vector2f objectSize = object.GetSize() / 2.f;

	sf::Vector2f pos = square.getPosition();
	sf::Vector2f size = square.getSize() / 2.f;

	float dx = objectPos.x - pos.x;
	float dy = objectPos.y - pos.y;

	float ix = abs(dx) - (objectSize.x + size.x);
	float iy = abs(dy) - (objectSize.y + size.y);

	if (ix < 0.f && iy < 0.f)
	{
		push = std::clamp(push, 0.f, 1.f);

		if (ix > iy)
		{
			if (dx > 0.f)
			{
				square.move(ix * (1.f - push), 0.f);
				object.move(-ix * push, 0.f);
			}

			else
			{
				square.move(-ix * (1.f - push), 0.f);
				object.move(ix * push, 0.f);
			}

			vel.x *= dampingFactor;
		}

		else
		{
			if (dy > 0.f)
			{
				square.move(0.f, iy * (1.f - push));
				object.move(0.f, -iy * push);
			}

			else
			{
				square.move(0.f, -iy * (1.f - push));
				object.move(0.f, iy * push);
			}

			vel.x /= SQUARE_FRICTION;
			vel.y *= dampingFactor;
		}

		isSpawn = true;
	}
}


void Rigid::checkCollisionWithCircleToObjects(Objects& object, float push)
{
	float dx = circle.getPosition().x - object.GetPosition().x;
	float dy = circle.getPosition().y - object.GetPosition().y;

	float ix = abs(dx) - ((object.GetSize().x / 2.f) + (circle.getRadius()));
	float iy = abs(dy) - ((object.GetSize().y / 2.f) + (circle.getRadius()));

	if (ix < 0.f && iy < 0.f)
	{
		push = std::clamp(push, 0.f, 1.f);

		if (ix > iy)
		{
			if (dx > 0.f)
			{
				circle.move(-ix * (1.f - push), 0.f);
				object.move(ix * push, 0.f);
			}

			else
			{
				circle.move(ix * (1.f - push), 0.f);
				object.move(-ix * push, 0.f);
			}

			vel2.x *= dampingFactor;
		}

		else
		{
			if (dy > 0.f)
			{
				circle.move(0.f, -iy * (1.f - push));
				object.move(0.f, iy * push);
			}

			else
			{
				circle.move(0.f, iy * (1.f - push));
				object.move(0.f, -iy * push);
			}

			vel2.x /= CIRCLE_FRICTION;
			vel2.y *= dampingFactor;
		}

		isSpawn = true;
	}
}

void Rigid::checkCollisionWithCircleToSquare()
{
	sf::Vector2f circlePos = circle.getPosition();
	float circleRadius = circle.getRadius();

	sf::Vector2f squarePos = square.getPosition();
	sf::Vector2f squareSize = square.getSize() / 2.f;

	float dx = circlePos.x - squarePos.x;
	float dy = circlePos.y - squarePos.y;

	float ix = abs(dx) - (squareSize.x + circleRadius);
	float iy = abs(dy) - (squareSize.y + circleRadius);

	if (ix < 0.f && iy < 0.f)
	{
		if (ix > iy)
		{
			if (dx > 0.f)
			{
				push = 0.f;

				circle.move(-ix * (1.f - push), 0.f);
				square.move(ix * push, 0.f);

				vel2.x -= 1.f;
			}

			else
			{
				push = 0.f;

				circle.move(ix * (1.f - push), 0.f);
				square.move(-ix * push, 0.f);

				vel2.x += 1.f;
			}

			vel2.x *= -0.25f;
		}

		else
		{
			if (dy > 0.f)
			{
				push = 1.f;

				circle.move(0.f, -iy * (1.f - push));
				square.move(0.f, iy * push);

				vel.x *= 0.5f;
				vel.y *= dampingFactor;
			}

			else
			{
				push = 0.f;

				circle.move(0.f, iy * (1.f - push));
				square.move(0.f, -iy * push);
			}

			vel2.y *= dampingFactor;
		}

		isSpawn = true;
	}
}

void Rigid::Draw(sf::RenderWindow& window)
{
	window.draw(square);
	window.draw(circle);
}