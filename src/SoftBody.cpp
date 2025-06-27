// CHECK OUT MY SOFTBODY PHYSICS SIMULATION TO UNDERSTAND HOW THIS WORKS :)

#include <SoftBody.hpp>

SoftBody::SoftBody(float restitution, float dampingFactor, float springConst)
	: restitution(restitution), dampingFactor(dampingFactor), springConst(springConst) { }

void SoftBody::addPoint(sf::Vector2f vertex)
{
	softBody.push_back(vertex);

	sf::Vector2f zero = { 0.f, 0.f };

	force = zero;
	velocity.push_back(zero);

	for (int i = 0; i < softBody.size(); i++)
	{
		for (int j = 0; j < softBody.size(); j++)
		{
			if (i != j)
			{
				sf::Vector2f distance = { (softBody[j].x - softBody[i].x) / 100.f, (softBody[j].y - softBody[i].y) / 100.f };
				springLength[i][j] = Magnitude(distance);
			}
		}
	}
}

void SoftBody::acceleratePoints()
{
	std::vector<sf::Vector2f> softBodyCopy = softBody;
	std::vector<sf::Vector2f> velCopy = velocity;

	for (int i = 0; i < softBody.size(); i++)
	{
		force = { 0.f, 0.f };

		for (int j = 0; j < softBody.size(); j++)
		{
			sf::Vector2f distance = { (softBody[j].x - softBody[i].x) / 100.f, (softBody[j].y - softBody[i].y) / 100.f };

			if (Magnitude(distance) != 0.f)
			{
				float tan = atan2(distance.y, distance.x);
				float magnitude = Magnitude(distance);
				float displacement = magnitude - springLength[i][j];

				sf::Vector2f anew = { (springConst * displacement * cos(tan)) / 10000.f, (springConst * displacement * sin(tan)) / 10000.f };

				force += anew;
				force -= dampingFactor * magnitude * (velocity[i] - velocity[j]) / 100.f;
			}
		}
		velCopy[i].x += force.x;
		velCopy[i].y += force.y + 0.098f;

		softBodyCopy[i].x += velCopy[i].x;
		softBodyCopy[i].y += velCopy[i].y;
	}
	softBody = softBodyCopy;
	velocity = velCopy;
}

void SoftBody::checkCollisionWithWindow(sf::RenderWindow& window)
{
	for (int i = 0; i < softBody.size(); i++)
	{
		if (softBody[i].x > window.getSize().x || softBody[i].x <= 0.f)
		{
			velocity[i].x *= -restitution;
			velocity[i].y *= FRICTION; // Friction

			softBody[i].x = softBody[i].x > window.getSize().x / 2.f ? window.getSize().x - 1.f : 1.f;
		}

		if (softBody[i].y > window.getSize().y || softBody[i].y <= 0.f)
		{
			velocity[i].y *= -restitution;
			velocity[i].x *= FRICTION; // Friction

			softBody[i].y = softBody[i].y > window.getSize().y / 2.f ? window.getSize().y - 1.f : 1.f;
		}
	}
}

void SoftBody::checkCollisionWithObjects(Objects& object, float push)
{
	for (int i = 0; i < softBody.size(); i++)
	{
		float objectPosX = object.GetPosition().x;
		float objectPosY = object.GetPosition().y;
		float objectSizeX = object.GetSize().x / 2.f;
		float objectSizeY = object.GetSize().y / 2.f;
		
		float softBodyPosX = softBody[i].x;
		float softBodyPosY = softBody[i].y;
		float softBodySizeX = GetSize().x / 2.f;
		float softBodySizeY = GetSize().y / 2.f;

		float dx = objectPosX - softBodyPosX;
		float dy = objectPosY - softBodyPosY;

		float ix = abs(dx) - (objectSizeX + softBodySizeX);
		float iy = abs(dy) - (objectSizeY + softBodySizeY);

		if (ix < 0.f && iy < 0.f)
		{
			push = std::clamp(push, 0.f, 1.f);

			if (ix > iy)
			{
				if (dx > 0.f)
				{
					moveForCollision(ix * (1.f - push), 0.f);
					object.move(-ix * push, 0.f);
				}

				else
				{
					moveForCollision(-ix * (1.f - push), 0.f);
					object.move(ix * push, 0.f);
				}

				velocity[i].x *= -restitution;
				velocity[i].y *= FRICTION; // Friction
			}

			else
			{
				if (dy > 0.f)
				{
					moveForCollision(0.f, iy * (1.f - push));
					object.move(0.f, -iy * push);
				}

				else
				{
					moveForCollision(0.f, -iy * (1.f - push));
					object.move(0.f, iy * push);
				}

				velocity[i].y *= -restitution;
				velocity[i].x *= FRICTION; // Friction
			}
		}
	}
}

void SoftBody::checkCollisionWithSquare(Rigid& rigid, float push)
{
	for (int i = 0; i < softBody.size(); i++)
	{
		sf::Vector2f squarePos = rigid.square.getPosition();
		sf::Vector2f squareSize = rigid.square.getSize() / 1.7f;

		sf::Vector2f softBodyPos = softBody[i];
		sf::Vector2f softBodySize = GetSize();

		float dx = squarePos.x - softBodyPos.x;
		float dy = squarePos.y - softBodyPos.y;

		float ix = abs(dx) - (squareSize.x + softBodySize.x);
		float iy = abs(dy) - (squareSize.y + softBodySize.y);

		if (ix < 0.f && iy < 0.f)
		{
			if (ix > iy)
			{
				if (dx > 0.f)
				{
					moveForCollision(ix * (1.f - push), 0.f);
					rigid.square.move(-ix * push, 0.f);
				}

				else
				{
					moveForCollision(-ix * (1.f - push), 0.f);
					rigid.square.move(ix * push, 0.f);
				}
			}

			else
			{
				if (dy > 0.f)
				{
					moveForCollision(0.f, iy * (1.f - push));
					rigid.square.move(0.f, -iy * 0.f);
				}

				else
				{
					moveForCollision(0.f, -iy * (1.f - push));
					rigid.square.move(0.f, iy * push);
				}

				rigid.vel.y *= 0.9f;
			}

			velocity[i] *= -restitution;
		}
	}
}

void SoftBody::checkCollisionWithCircle(Rigid& rigid, float push)
{
	for (int i = 0; i < softBody.size(); i++)
	{
		sf::Vector2f circlePosition = rigid.circle.getPosition();
		float circleRadius = rigid.circle.getRadius() * 1.1f;

		sf::Vector2f softBodyPosition = softBody[i];
		sf::Vector2f softBodySize = GetSize();

		float dx = softBodyPosition.x - circlePosition.x;
		float dy = softBodyPosition.y - circlePosition.y;

		float ix = abs(dx) - (softBodySize.x + circleRadius);
		float iy = abs(dy) - (softBodySize.y + circleRadius);

		if (ix < 0.f && iy < 0.f)
		{
			if (ix > iy)
			{
				if (dx < 0.f)
				{
					moveForCollision(ix * (1.f - push), 0.f);
					rigid.circle.move(-ix * push, 0.f);
				}

				else
				{
					moveForCollision(-ix * (1.f - push), 0.f);
					rigid.circle.move(ix * push, 0.f);
				}
			}

			else
			{
				if (dy < 0.f)
				{
					moveForCollision(0.f, iy * (1.f - push));
					rigid.circle.move(0.f, -iy * push);
				}

				else
				{
					moveForCollision(0.f, -iy * (1.f - push));
					rigid.circle.move(0.f, iy * push);
				}

				rigid.vel2.y *= 0.9f;
			}
			force = { 0.f, 0.f };
			velocity[i] *= -restitution;
		}
	}
}

void SoftBody::Move(float speed)
{
	for (int i = 0; i < softBody.size(); i++)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			velocity[i].y -= speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			velocity[i].y += speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			velocity[i].x += speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			velocity[i].x -= speed;
	}
}

void SoftBody::drawLine(sf::RenderWindow& window, sf::Vector2f a, sf::Vector2f b, sf::Color color)
{
	sf::Vertex vertex[] =
	{
			sf::Vertex(sf::Vector2f(a.x, a.y), color),
		sf::Vertex(sf::Vector2f(b.x, b.y), color)
	};

	window.draw(vertex, 2, sf::Lines);
}

void SoftBody::Draw(sf::RenderWindow& window, sf::Color color)
{
	for (int i = 0; i < softBody.size(); i++)
		drawLine(window, softBody[i], softBody[(i + 1) % softBody.size()], color);
}

void SoftBody::clear()
{
	softBody.clear();
	velocity.clear();
}