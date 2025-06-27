#include <Pendulum.hpp>

Pendulum::Pendulum(int mass, int l, int x, int y)
{
	aAcel = 0.f;
	aVel = 0.f;
	Theta = 0.f;
	Theta = Theta * PI / 180.f;

	dragEnable = false;
	dragDisable = false;

	this->mass = mass;
	this->l = l;

	arm.setSize(sf::Vector2f(5.f, l));
	arm.setOrigin(arm.getSize().x / 2.f, 0.f);
	arm.setPosition(this->x, this->y);
	arm.setRotation(Theta * 180.f / PI);
	arm.setFillColor(sf::Color::Black);

	bob.setRadius(15.f);
	bob.setOrigin(bob.getRadius(), bob.getRadius());
	bob.setPosition(getXPoint(), getYPoint());
	bob.setFillColor(sf::Color::Red);

	this->x = x;
	this->y = y;
}

void Pendulum::setScale(sf::Vector2f scale)
{
	arm.setScale(scale);
	bob.setScale(scale);
}

void Pendulum::Update(sf::Vector2i pos)
{
	if (!isDragPendulum(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		dragDisable = true;

	if (dragDisable)
	{
		aAcel = (-Gravity / l) * sin(Theta);
		aVel += aAcel;
		aVel *= dampingFactor;
		Theta += aVel;
	}

	arm.setPosition(x, y);
	arm.setRotation(Theta * 180.f / PI);
	bob.setPosition(getXPoint(), getYPoint());
}

void Pendulum::dragPendulum(sf::Vector2i pos)
{
	if (isDragPendulum(pos))
	{
		aVel = 0.f;

		if (pos.x <= 499.f)
			Theta += 0.025f;

		else if (pos.x >= 499.f)
			Theta -= 0.025f;

		arm.setRotation(Theta);
		bob.setPosition(l, pos.y);
	}
}

bool Pendulum::isMouseClickedOnBob(sf::Vector2i pos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (bob.getGlobalBounds().contains(sf::Vector2f(pos)))
		{
			return true;
		}
	}
	
	return false;
}

bool Pendulum::isDragPendulum(sf::Vector2i pos)
{
	isMouseClickedOnBob(pos);

	if (isMouseClickedOnBob(pos))
	{
		dragEnable = true;
		dragDisable = false;
	}

	if (!isMouseClickedOnBob(pos))
		dragEnable = false;

	return dragEnable;
}

void Pendulum::Draw(sf::RenderWindow& window)
{
	window.draw(arm);
	window.draw(bob);
}
