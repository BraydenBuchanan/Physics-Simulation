#include <DoublePendulum.hpp>

DoublePendulum::DoublePendulum(int mass, int length, int x, int y)
{
	aAcel = 0.f;
	aVel = 0.f;
	Theta = 0.f;
	Theta = Theta * PI / 180.f;

	this->mass = mass;
	this->length = length;

	dragEnable = false;
	dragDisable = false;

	arm = sf::RectangleShape(sf::Vector2f(5.f, length));
	arm.setOrigin(arm.getSize().x / 2.f, 0.f);
	arm.setPosition(this->x, this->y);
	arm.setFillColor(sf::Color::Black);
	arm.setRotation(Theta * 180.f / PI);
	arm.setScale(0.f, 0.f);

	bob = sf::CircleShape(15.f);
	bob.setOrigin(bob.getRadius(), bob.getRadius());
	bob.setPosition(getXPoint(), getYPoint());
	bob.setFillColor(sf::Color::Red);
	bob.setScale(0.f, 0.f);

	this->x = x;
	this->y = y;
}

DoublePendulum::DoublePendulum(int mass, int length, DoublePendulum* lowerPendulum)
{
	aAcel = 0.f;
	aVel = 0.f;
	Theta = 0.f;
	Theta = Theta * PI / 180.f;

	this->mass = mass;
	this->length = length;

	dragEnable = false;
	dragDisable = false;

	arm = sf::RectangleShape(sf::Vector2f(5.f, length));
	arm.setOrigin(arm.getSize().x / 2.f, 0.f);
	arm.setPosition(this->x, this->y);
	arm.setFillColor(sf::Color::Black);
	arm.setRotation(Theta * 180.f / PI);
	arm.setScale(0.f, 0.f);

	bob = sf::CircleShape(15.f);
	bob.setOrigin(bob.getRadius(), bob.getRadius());
	bob.setPosition(getXPoint(), getYPoint());
	bob.setFillColor(sf::Color::Red);
	bob.setScale(0.f, 0.f);

	this->lowerPendulum = lowerPendulum;
	this->x = lowerPendulum->getXPoint();
	this->y = lowerPendulum->getYPoint();
}

void DoublePendulum::setScale(sf::Vector2f scale)
{
	arm.setScale(scale);
	bob.setScale(scale);

	lowerPendulum->arm.setScale(scale);
	lowerPendulum->bob.setScale(scale);
}

void DoublePendulum::Update(sf::Vector2i pos)  
{  
   bool isDragging = isDragPendulum(pos);  

   if (!isDragging && sf::Mouse::isButtonPressed(sf::Mouse::Right))  
       dragDisable = true;  

   if (dragDisable)  
   {  
       aVel += aAcel;  
       Theta += aVel;  
       aVel *= dampingFactor;  
   }  

   if (lowerPendulum && !isDragging)  
   {  
       lowerPendulum->Update(pos);  

	   x = lowerPendulum->getXPoint();
	   y = lowerPendulum->getYPoint();
   }  

   arm.setPosition(x, y);  
   arm.setRotation(Theta * 180.f / PI);  
   bob.setPosition(arm.getPosition().x - length * sin(Theta), arm.getPosition().y + length * cos(Theta));  

   if (lowerPendulum)  
   {  
       if (dragDisable)  
       {  
           float mass1 = lowerPendulum->mass;  
           float mass2 = mass;  

           float Theta1 = lowerPendulum->Theta;  
           float Theta2 = Theta;  

           float length1 = lowerPendulum->length;  
           float length2 = length;  

           float aVel1 = lowerPendulum->aVel;  
           float aVel2 = aVel;  

           float sec1 = -Gravity * (2.f * mass1 + mass2) * sin(Theta1);  
           float sec2 = -mass2 * Gravity * sin(Theta1 - 2.f * Theta2);  
           float sec3 = -2.f * sin(Theta1 - Theta2) * mass2 * (aVel2 * aVel2 * length2 + aVel1 * aVel1 * length1 * cos(Theta1 - Theta2));  
           float denominator = length1 * (2.f * mass1 + mass2 - mass2 * cos(2 * Theta1 - 2 * Theta2));  

           lowerPendulum->aAcel = (sec1 + sec2 + sec3) / denominator;  

           sec1 = 2.f * sin(Theta1 - Theta2);  
           sec2 = aVel1 * aVel1 * length1 * (mass1 + mass2);  
           sec3 = Gravity * (mass1 + mass2) * cos(Theta1) + aVel2 * aVel2 * length2 * mass2 * cos(Theta1 - Theta2);  
           denominator = length2 * (2.f * mass1 + mass2 - mass2 * cos(2 * Theta1 - 2.f * Theta2));  

           aAcel = (sec1 * (sec2 + sec3)) / denominator;  
       }  
   }  
}

void DoublePendulum::dragPendulum(sf::Vector2i pos)
{
	if (isDragPendulum(pos))
	{
		aVel = 0.f;

		dragDisable = false;

		if (pos.x <= 499.f)
			Theta += 0.025f;

		else if (pos.x >= 499.f)
			Theta -= 0.025f;

		arm.setRotation(Theta);
		bob.setPosition(length, pos.y);
	}
}

bool DoublePendulum::isMouseClickedOnBob(sf::Vector2i pos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (bob.getGlobalBounds().contains((sf::Vector2f)pos))
			return true;
	}
	return false;
}

bool DoublePendulum::isDragPendulum(sf::Vector2i pos) 
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

void DoublePendulum::Draw(sf::RenderWindow& window)
{
	window.draw(arm);
	window.draw(bob);
}