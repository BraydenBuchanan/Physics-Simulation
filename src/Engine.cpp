#include <Engine.hpp>

Engine::Engine()
{
	font.loadFromFile(assets.font);

	toggled = false;
	toggled2 = false;
	toggled3 = false;
    
	disableRBpanel = false;
	disablePENpanel = false;
	disableSBpanel = false;

	// RIGID BODY:
	RBstatusBool = false;
	RBsquareActivate = false;
	RBcircleActivate = false;
	allowSquareToSpawn = false;
	allowCircleToSpawn = false;

	RBstatusOnOrOff = "Off";
	RBstatusString = "Rigid Body Status: " + RBstatusOnOrOff;

	barSelect.setSize(sf::Vector2f(250.f, 1000.f));
	barSelect.setPosition(750.f, 0.f);
	barSelect.setFillColor(sf::Color(156.f, 156.f, 156.f));
	barSelect.setOutlineThickness(3.f);
	barSelect.setOutlineColor(sf::Color::Black);

	RBbutton.setSize(sf::Vector2f(100.f, 50.f));
	RBbutton.setOutlineThickness(3.f);
	RBbutton.setOutlineColor(sf::Color::Black);

	RBtxt.setString("Rigid Bodies");
	RBtxt.setCharacterSize(15.f);
	RBtxt.setFillColor(sf::Color::Black);
	RBtxt.setFont(font);

	RBstatusTxt.setString(RBstatusString);
	RBstatusTxt.setCharacterSize(15.f);
	RBstatusTxt.setFillColor(sf::Color::Black);
	RBstatusTxt.setFont(font);
	/****************************************************/

	// PENDULUM:
	pendulumActivate = false;
	doublePendulumActivate = false;
	allowPendulumToSpawn = false;
	allowDoublePendulumToSpawn = false;

	PENstatusTxt.setPosition(0.f, 18.f);
	PENstatusBool = false;

	PENstatusOnOrOff = "Off";
	PENstatusString = "Pendulum Status: " + PENstatusOnOrOff;

	PENbutton.setSize(sf::Vector2f(100.f, 50.f));
	PENbutton.setOutlineThickness(3.f);
	PENbutton.setOutlineColor(sf::Color::Black);

	PENtxt.setString("Pendulums");
	PENtxt.setCharacterSize(15.f);
	PENtxt.setFillColor(sf::Color::Black);
	PENtxt.setFont(font);

	PENstatusTxt.setString(PENstatusString);
	PENstatusTxt.setCharacterSize(15.f);
	PENstatusTxt.setFillColor(sf::Color::Black);
	PENstatusTxt.setFont(font);
	/****************************************************/

	// SOFTBODY:
	softBodyActivate = false;
	allowSoftBodyToSpawn = false;

	SBstatusTxt.setPosition(0.f, 36.f);
	SBstatusBool = false;

	SBstatusOnOrOff = "Off";
	SBstatusString = "Soft Body Status: " + SBstatusOnOrOff;

	SBbutton.setSize(sf::Vector2f(100.f, 50.f));
	SBbutton.setOutlineThickness(3.f);
	SBbutton.setOutlineColor(sf::Color::Black);

	SBtxt.setString("Soft Body");
	SBtxt.setCharacterSize(15.f);
	SBtxt.setFillColor(sf::Color::Black);
	SBtxt.setFont(font);

	SBstatusTxt.setString(SBstatusString);
	SBstatusTxt.setCharacterSize(15.f);
	SBstatusTxt.setFillColor(sf::Color::Black);
	SBstatusTxt.setFont(font);
	/****************************************************/
}

bool Engine::isMouseOverSelectBar(sf::Vector2i pos)
{
	RBsquareActivate = false;
	RBcircleActivate = false;

	pendulumActivate = false;
	doublePendulumActivate = false;

	softBodyActivate = false;

	return barSelect.getGlobalBounds().contains((sf::Vector2f)pos);
}

// RIGID BODY:
bool Engine::isMouseOverRBpanels(sf::Vector2i pos)
{
	RBsquareActivate = false;
	RBcircleActivate = false;

	pendulumActivate = false;
	doublePendulumActivate = false;

	softBodyActivate = false;

	return RBpanel.getGlobalBounds().contains((sf::Vector2f)pos);
}

void Engine::setPosRBUI(sf::Vector2f pos)
{
	RBbutton.setPosition(pos.x, pos.y);

	RBtxt.setPosition(RBbutton.getPosition().x + (RBbutton.getSize().x - RBtxt.getLocalBounds().width) / 2.f,
		RBbutton.getPosition().y + (RBbutton.getSize().y - RBtxt.getLocalBounds().height) / 2.5f);
}

void Engine::setPosRBs(sf::Vector2f pos)
{
	RBselect1.setPosition(pos.x, pos.y);

	RBselectTxt.setPosition(RBselect1.getPosition().x + (RBselect1.getSize().x - RBselectTxt.getLocalBounds().width) / 2.f,
		RBselect1.getPosition().y + (RBselect1.getSize().y - RBselectTxt.getLocalBounds().height) / 2.5f);

	RBselect2.setPosition(pos.x, pos.y + 60.f);

	RBselectTxt2.setPosition(RBselect2.getPosition().x + (RBselect2.getSize().x - RBselectTxt2.getLocalBounds().width) / 2.f,
		RBselect2.getPosition().y + (RBselect2.getSize().y - RBselectTxt2.getLocalBounds().height) / 2.5f);

	RBreset.setPosition(pos.x + 15.f, pos.y + 121.f);

	RBresetTxt.setPosition(RBreset.getPosition().x + (RBreset.getSize().x - RBresetTxt.getLocalBounds().width) / 2.f,
		RBreset.getPosition().y + (RBreset.getSize().y - RBresetTxt.getLocalBounds().height) / 3.f);
}

bool Engine::isMouseClickedRBUI(sf::Vector2i pos)
{
	if (isMouseOverRBUI({ pos.x, pos.y }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

bool Engine::isMouseClickedRBsquare(sf::Vector2i pos)
{
	if (isMouseOverRBsquare({ pos.x, pos.y }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		allowSquareToSpawn = true;
		allowCircleToSpawn = false;

		allowPendulumToSpawn = false;
		allowDoublePendulumToSpawn = false;

		allowSoftBodyToSpawn = false;

		return true;
	}

	return false;
}

bool Engine::isMouseClickedRBcircle(sf::Vector2i pos)
{
	if (isMouseOverRBcircle({ pos.x, pos.y }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		allowSquareToSpawn = false;
		allowCircleToSpawn = true;

		allowPendulumToSpawn = false;
		allowDoublePendulumToSpawn = false;

		allowSoftBodyToSpawn = false;

		return true;
	}

	return false;
}

bool Engine::isMouseClickedRBreset(sf::Vector2i pos)
{
	if (isMouseOverRBreset({ pos.x, pos.y }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

void Engine::createRigidBodyPanel(sf::Vector2i pos)
{
	if (isMouseClickedRBUI({ pos.x, pos.y }) && !disableRBpanel)
	{
		toggled = !toggled;

		if (toggled)
		{
			disablePENpanel = true;
			disableSBpanel = true;

			std::this_thread::sleep_for(0.2s);

			RBpanel.setSize(sf::Vector2f(250.f, 250.f));
			RBpanel.setFillColor(sf::Color(156, 156, 156));
			RBpanel.setPosition(610.f, 130.f);
			RBpanel.setOrigin(RBpanel.getSize().x / 2.f, RBpanel.getSize().y / 2.f);
			RBpanel.setOutlineThickness(3.f);
			RBpanel.setOutlineColor(sf::Color::Black);

            RBpanelTxt.setScale(1.f, 1.f);
			RBpanelTxt.setString("Rigid Body Selection Interface");
			RBpanelTxt.setCharacterSize(15.f);
			RBpanelTxt.setFillColor(sf::Color::Black);
			RBpanelTxt.setFont(font);
			RBpanelTxt.setPosition(505.f, 10.f);

			RBselectTxt.setScale(1.f, 1.f);
			RBselectTxt.setString("Square");
			RBselectTxt.setCharacterSize(15.f);
			RBselectTxt.setFillColor(sf::Color::Black);
			RBselectTxt.setFont(font);

			RBselect1.setSize(sf::Vector2f(100.f, 50.f));
			RBselect1.setOutlineThickness(3.f);
			RBselect1.setOutlineColor(sf::Color::Black);

			RBselectTxt2.setScale(1.f, 1.f);
			RBselectTxt2.setString("Circle");
			RBselectTxt2.setCharacterSize(15.f);
			RBselectTxt2.setFillColor(sf::Color::Black);
			RBselectTxt2.setFont(font);

			RBselect2.setSize(sf::Vector2f(100.f, 50.f));
			RBselect2.setOutlineThickness(3.f);
			RBselect2.setOutlineColor(sf::Color::Black);

			RBresetTxt.setScale(1.f, 1.f);
			RBresetTxt.setString("Reset");
			RBresetTxt.setCharacterSize(15.f);
			RBresetTxt.setFillColor(sf::Color::Black);
			RBresetTxt.setFont(font);

			RBreset.setSize(sf::Vector2f(70.f, 30.f));
			RBreset.setOutlineThickness(3.f);
			RBreset.setOutlineColor(sf::Color::Black);

			RBinstructionsTxt.setScale({ 1.f, 1.f });
			RBinstructionsTxt.setCharacterSize(15.f);
			RBinstructionsTxt.setFont(font);
			RBinstructionsTxt.setFillColor(sf::Color::Black);
			RBinstructionsTxt.setString("Spawn and activate a sqaure \nor circle rigid body by \nleft clicking anywhere.");
			RBinstructionsTxt.setPosition({ 490.f, 195.f });

			setPosRBs({ 563.f, 40.f });
		}

		else
		{
			disablePENpanel = false;
			disableSBpanel = false;

			std::this_thread::sleep_for(0.2s);

			RBpanel.setSize(sf::Vector2f(0.f, 0.f));

			RBselect1.setSize(sf::Vector2f(0.f, 0.f));
			RBselectTxt.setScale(0.f, 0.f);

			RBselect2.setSize(sf::Vector2f(0.f, 0.f));
			RBselectTxt2.setScale(0.f, 0.f);

			RBreset.setSize(sf::Vector2f(0.f, 0.f));
			RBresetTxt.setScale(0.f, 0.f);

			RBinstructionsTxt.setScale({ 0.f, 0.f });

			RBpanelTxt.setScale(0.f, 0.f);
		}
	}
}

void Engine::setRBstatus(sf::Vector2i pos)
{
	if (isMouseClickedRBreset({pos.x, pos.y}))
	{
		RBstatusBool = false;
		RBstatusOnOrOff = "Off";
		RBstatusString = "Rigid Body Status: " + RBstatusOnOrOff;
		RBstatusTxt.setString(RBstatusString);
	}

	else
	{
		RBstatusBool = true;
		RBstatusOnOrOff = "On";
		RBstatusString = "Rigid Body Status: " + RBstatusOnOrOff;
		RBstatusTxt.setString(RBstatusString);
	}
}

bool Engine::isSpawnRBsquare(sf::Vector2i pos)
{
	if (!isMouseOverSelectBar(pos) && !isMouseOverRBpanels(pos) && !isMouseOverPENpanel(pos) && !isMouseOverSBpanel(pos) && RBstatusBool && allowSquareToSpawn)
		RBsquareActivate = true;

	if (RBsquareActivate && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

bool Engine::isSpawnRBcircle(sf::Vector2i pos)
{
	if (!isMouseOverSelectBar(pos) && !isMouseOverRBpanels(pos) && !isMouseOverPENpanel(pos) && !isMouseOverSBpanel(pos) && RBstatusBool && allowCircleToSpawn)
		RBcircleActivate = true;

	if (RBcircleActivate && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}
/****************************************************/

// PENDULUM:

bool Engine::isMouseOverPENpanel(sf::Vector2i pos)
{
	RBcircleActivate = false;
	RBsquareActivate = false;

	pendulumActivate = false;
	doublePendulumActivate = false;

	return PENpanel.getGlobalBounds().contains(sf::Vector2f(pos));
}

void Engine::setPosPENUI(sf::Vector2f pos)
{
	PENbutton.setPosition(pos.x, pos.y);

	PENtxt.setPosition(PENbutton.getPosition().x + (PENbutton.getSize().x - PENtxt.getLocalBounds().width / 0.85f),
		PENbutton.getPosition().y + (PENbutton.getSize().y - PENtxt.getLocalBounds().height / 0.33f));
}

void Engine::setPosPENS(sf::Vector2f pos)
{
	doublePendulumButton.setPosition(pos.x, pos.y);

	doublePendulumTxt.setPosition(doublePendulumButton.getPosition().x + (doublePendulumButton.getSize().x - doublePendulumTxt.getLocalBounds().width / 0.92f),
		doublePendulumButton.getPosition().y + (doublePendulumButton.getSize().y - doublePendulumTxt.getLocalBounds().height / 0.28f));

	pendulumButton.setPosition(pos.x, pos.y + 60.f);

	pendulumTxt.setPosition(pendulumButton.getPosition().x + (pendulumButton.getSize().x - pendulumTxt.getLocalBounds().width / 0.80f),
		pendulumButton.getPosition().y + (pendulumButton.getSize().y - pendulumTxt.getLocalBounds().height / 0.33f));

	PENreset.setPosition(pos.x + 15.f, pos.y + 121.f);

	PENresetTxt.setPosition(PENreset.getPosition().x + (PENreset.getSize().x - PENresetTxt.getLocalBounds().width / 0.73f),
		PENreset.getPosition().y + (PENreset.getSize().y - PENresetTxt.getLocalBounds().height / 0.45f));
}

bool Engine::isMouseClickedPENUI(sf::Vector2i pos)
{
	if (isMouseOverPENUI(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
}

bool Engine::isMouseClickedDPB(sf::Vector2i pos)
{
	if (isMouseOverDPB(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		allowSquareToSpawn = false;
		allowCircleToSpawn = false;

		allowPendulumToSpawn = false;
		allowDoublePendulumToSpawn = true;

		allowSoftBodyToSpawn = false;

		return true;
	}
}

bool Engine::isMouseClickedPB(sf::Vector2i pos)
{
	if (isMouseOverPB(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		allowSquareToSpawn = false;
		allowCircleToSpawn = false;

		allowPendulumToSpawn = true;
		allowDoublePendulumToSpawn = false;

		allowSoftBodyToSpawn = false;

		return true;
	}
}

bool Engine::isMouseClickedPENreset(sf::Vector2i pos)
{
	if (isMouseOverPENreset(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
}

void Engine::setPENstatus(sf::Vector2i pos)
{
	if (isMouseClickedPENreset(pos))
	{
		PENstatusBool = false;
		PENstatusOnOrOff = "Off";
		PENstatusString = "Pendulum Status: " + PENstatusOnOrOff;
		PENstatusTxt.setString(PENstatusString);
	}

	else
	{
		PENstatusBool = true;
		PENstatusOnOrOff = "On";
		PENstatusString = "Pendulum Status: " + PENstatusOnOrOff;
		PENstatusTxt.setString(PENstatusString);
	}
}

void Engine::createPendulumPanel(sf::Vector2i pos)
{
	if (isMouseClickedPENUI(pos) && !disablePENpanel)
	{
		toggled2 = !toggled2;

		if (toggled2)
		{
			disableRBpanel = true;
			disableSBpanel = true;

			std::this_thread::sleep_for(0.2s);

			PENpanel.setScale(1.f, 1.f);
			PENpanel.setSize(sf::Vector2f(250.f, 330.f));
			PENpanel.setFillColor(sf::Color(156, 156, 156));
			PENpanel.setPosition(610.f, 170.f);
			PENpanel.setOrigin(PENpanel.getSize().x / 2.f, PENpanel.getSize().y / 2.f);
			PENpanel.setOutlineThickness(3.f);
			PENpanel.setOutlineColor(sf::Color::Black);

			PENpanelTxt.setScale(1.f, 1.f);
			PENpanelTxt.setFont(font);
			PENpanelTxt.setCharacterSize(15.f);
			PENpanelTxt.setPosition(505.f, 10.f);
			PENpanelTxt.setString("Pendulum Selection Interface");
			PENpanelTxt.setFillColor(sf::Color::Black);

			doublePendulumButton.setScale(1.f, 1.f);
			doublePendulumButton.setSize(sf::Vector2f(100.f, 50.f));
			doublePendulumButton.setOutlineColor(sf::Color::Black);
			doublePendulumButton.setOutlineThickness(3.f);

			doublePendulumTxt.setScale(1.f, 1.f);
			doublePendulumTxt.setFont(font);
			doublePendulumTxt.setCharacterSize(12.f);
			doublePendulumTxt.setString("Double Pendulum");
			doublePendulumTxt.setFillColor(sf::Color::Black);

			pendulumButton.setScale(1.f, 1.f);
			pendulumButton.setSize(sf::Vector2f(100.f, 50.f));
			pendulumButton.setOutlineColor(sf::Color::Black);
			pendulumButton.setOutlineThickness(3.f);

			pendulumTxt.setScale(1.f, 1.f);
			pendulumTxt.setFont(font);
			pendulumTxt.setCharacterSize(15.f);
			pendulumTxt.setString("Pendulum");
			pendulumTxt.setFillColor(sf::Color::Black);

			PENreset.setScale(1.f, 1.f);
			PENreset.setSize(sf::Vector2f(70.f, 30.f));
			PENreset.setOutlineColor(sf::Color::Black);
			PENreset.setOutlineThickness(3.f);

			PENresetTxt.setScale(1.f, 1.f);
			PENresetTxt.setFont(font);
			PENresetTxt.setCharacterSize(15.f);
			PENresetTxt.setString("Reset");
			PENresetTxt.setFillColor(sf::Color::Black);

			PENinstructionsTxt.setScale({ 1.f, 1.f });
			PENinstructionsTxt.setFont(font);
			PENinstructionsTxt.setCharacterSize(15.f);
			PENinstructionsTxt.setString("Create either a regular pendulum \nor double pendulum by left \nclicking anywhere, then click the \npendulum's bob and drag the \npendulum to any position. Finally \nright click to activate the \npendulum");
			PENinstructionsTxt.setFillColor(sf::Color::Black);
			PENinstructionsTxt.setPosition(490.f, 200.f);

			setPosPENS({ 563.f, 40.f });
		}

		else
		{
			disableRBpanel = false;
			disableSBpanel = false;

			std::this_thread::sleep_for(0.2s);

			PENpanel.setScale(0.f, 0.f);
			PENpanelTxt.setScale(0.f, 0.f);

			doublePendulumButton.setScale(0.f, 0.f);
			doublePendulumTxt.setScale(0.f, 0.f);

			pendulumButton.setScale(0.f, 0.f);
			pendulumTxt.setScale(0.f, 0.f);

			PENreset.setScale(0.f, 0.f);
			PENresetTxt.setScale(0.f, 0.f);

			PENinstructionsTxt.setScale({ 0.f, 0.f });
		}
	}
}

bool Engine::isSpawnPendulum(sf::Vector2i pos)
{
	if (!isMouseOverSelectBar(pos) && !isMouseOverRBpanels(pos) && !isMouseOverPENpanel(pos) && !isMouseOverSBpanel(pos) && PENstatusBool && allowPendulumToSpawn)
		pendulumActivate = true;

	if (pendulumActivate && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

bool Engine::isSpawnDPendulum(sf::Vector2i pos)
{
	if (!isMouseOverSelectBar(pos) && !isMouseOverRBpanels(pos) && !isMouseOverPENpanel(pos) && !isMouseOverSBpanel(pos) && PENstatusBool && allowDoublePendulumToSpawn)
		doublePendulumActivate = true;

	if (doublePendulumActivate && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

/****************************************************/

// SOFTBODY:

void Engine::setPosSBUI(sf::Vector2f pos)
{
	SBbutton.setPosition(pos.x, pos.y);

	SBtxt.setPosition(SBbutton.getPosition().x + (SBbutton.getSize().x - SBtxt.getLocalBounds().width) / 2.f,
		SBbutton.getPosition().y + (SBbutton.getSize().y - SBtxt.getLocalBounds().height) / 2.5f);
}

void Engine::setPosSB(sf::Vector2f pos)
{
	SBAbutton.setPosition(pos.x, pos.y);

	SBAtxt.setPosition(SBAbutton.getPosition().x + (SBAbutton.getSize().x - SBAtxt.getLocalBounds().width) / 2.f,
		SBAbutton.getPosition().y + (SBAbutton.getSize().y - SBAtxt.getLocalBounds().height) / 2.5f);

	SBreset.setPosition(pos.x + 15.f, pos.y + 60.f);

	SBresetTxt.setPosition(SBreset.getPosition().x + (SBreset.getSize().x - SBresetTxt.getLocalBounds().width) / 2.f,
		SBreset.getPosition().y + (SBreset.getSize().y - SBresetTxt.getLocalBounds().height) / 2.5f);
}

bool Engine::isMouseClickedSBUI(sf::Vector2i pos)
{
	if (isMouseOverSBUI(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

bool Engine::isMouseClickedSBAB(sf::Vector2i pos)
{
	if (isMouseOverSBAB(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		allowSquareToSpawn = false;
		allowCircleToSpawn = false;

		allowPendulumToSpawn = false;
		allowDoublePendulumToSpawn = false;

		allowSoftBodyToSpawn = true;

		return true;
	}

	return false;
}

bool Engine::isMouseClickedSBreset(sf::Vector2i pos)
{
	if (isMouseOverSBreset(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

void Engine::setSBstatus(sf::Vector2i pos)
{
	if (isMouseClickedSBreset(pos))
	{
		SBstatusBool = false;
		SBstatusOnOrOff = "Off";
		SBstatusString = "Soft Body Status: " + SBstatusOnOrOff;
		SBstatusTxt.setString(SBstatusString);
	}

	else
	{
		SBstatusBool = true;
		SBstatusOnOrOff = "On";
		SBstatusString = "Soft Body Status: " + SBstatusOnOrOff;
		SBstatusTxt.setString(SBstatusString);
		
	}
	
}

void Engine::createSoftbodyPanel(sf::Vector2i pos)
{
	if (isMouseClickedSBUI(pos) && !disableSBpanel)
	{
		toggled3 = !toggled3;

		if (toggled3)
		{
			disablePENpanel = true;
			disableRBpanel = true;

			std::this_thread::sleep_for(0.2s);

			SBpanel.setScale(1.f, 1.f);
			SBpanel.setSize(sf::Vector2f(250.f, 250.f));
			SBpanel.setFillColor(sf::Color(156, 156, 156));
			SBpanel.setPosition(610.f, 130.f);
			SBpanel.setOrigin(SBpanel.getSize().x / 2.f, SBpanel.getSize().y / 2.f);
			SBpanel.setOutlineThickness(3.f);
			SBpanel.setOutlineColor(sf::Color::Black);

			SBpanelTxt.setScale(1.f, 1.f);
			SBpanelTxt.setFont(font);
			SBpanelTxt.setCharacterSize(15.f);
			SBpanelTxt.setPosition(505.f, 10.f);
			SBpanelTxt.setString("Soft Body Selection Interface");
			SBpanelTxt.setFillColor(sf::Color::Black);

			SBAbutton.setScale(1.f, 1.f);
			SBAbutton.setSize(sf::Vector2f(100.f, 50.f));
			SBAbutton.setOutlineThickness(3.f);
			SBAbutton.setOutlineColor(sf::Color::Black);

			SBAtxt.setScale(1.f, 1.f);
			SBAtxt.setCharacterSize(15.f);
			SBAtxt.setString("Soft Body");
			SBAtxt.setFillColor(sf::Color::Black);
			SBAtxt.setFont(font);

			SBreset.setScale(1.f, 1.f);
			SBreset.setSize(sf::Vector2f(70.f, 30.f));
			SBreset.setOutlineThickness(3.f);
			SBreset.setOutlineColor(sf::Color::Black);

			SBresetTxt.setScale(1.f, 1.f);
			SBresetTxt.setCharacterSize(15.f);
			SBresetTxt.setString("Reset");
			SBresetTxt.setFillColor(sf::Color::Black);
			SBresetTxt.setFont(font);

			SBinstructionsTxt.setScale({ 1.f, 1.f });
			SBinstructionsTxt.setCharacterSize(15.f);
			SBinstructionsTxt.setString("Create a soft body shape by left \nclicking anywhere to plot \na point, then right \nclick to actiavte the soft body. \nUse WASD or arrow keys to \nmove the soft body.");
			SBinstructionsTxt.setFillColor(sf::Color::Black);
			SBinstructionsTxt.setFont(font);
			SBinstructionsTxt.setPosition(490.f, 140.f);

			setPosSB({ 563.f, 40.f });
		}

		else
		{
			disablePENpanel = false;
			disableRBpanel = false;

			std::this_thread::sleep_for(0.2s);

			SBpanel.setScale(0.f, 0.f);
			SBpanelTxt.setScale(0.f, 0.f);
			
			SBAbutton.setScale(0.f, 0.f);
			SBAtxt.setScale(0.f, 0.f);

			SBreset.setScale(0.f, 0.f);
			SBresetTxt.setScale(0.f, 0.f);

			SBinstructionsTxt.setScale({ 0.f, 0.f });
		}
	}
}

bool Engine::isSpawnSoftBody(sf::Vector2i pos)
{
	if (!isMouseOverSelectBar(pos) && !isMouseOverRBpanels(pos) && !isMouseOverPENpanel(pos) && !isMouseOverSBpanel(pos) && SBstatusBool && allowSoftBodyToSpawn)
		softBodyActivate = true;

	else
		softBodyActivate = false;

	if (softBodyActivate && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

/****************************************************/

void Engine::Draw(sf::RenderWindow& window, sf::Vector2i pos)
{
	window.draw(barSelect);

	// RIGID BODY
	window.draw(RBpanel);
	window.draw(RBreset);
	window.draw(RBresetTxt);
	window.draw(RBselect2);
	window.draw(RBselectTxt2);
	window.draw(RBselect1);
	window.draw(RBselectTxt);
	window.draw(RBpanelTxt);
	window.draw(RBstatusTxt);
	window.draw(RBbutton);
	window.draw(RBtxt);
	window.draw(RBinstructionsTxt);

	/****************************************************/

	// PENDULUM
	window.draw(PENpanel);
	window.draw(PENreset);
	window.draw(PENresetTxt);
	window.draw(doublePendulumButton);
	window.draw(doublePendulumTxt);
	window.draw(pendulumButton);
	window.draw(pendulumTxt);
	window.draw(PENpanelTxt);
	window.draw(PENstatusTxt);
	window.draw(PENbutton);
	window.draw(PENtxt);
	window.draw(PENinstructionsTxt);

	/****************************************************/

	// SOFTBODY

	window.draw(SBpanel);
	window.draw(SBbutton);
	window.draw(SBtxt);
	window.draw(SBpanelTxt);
	window.draw(SBAbutton);
	window.draw(SBAtxt);
	window.draw(SBstatusTxt);
	window.draw(SBreset);
	window.draw(SBresetTxt);
	window.draw(SBinstructionsTxt);

	/****************************************************/
}