#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include <Objects.hpp>
#include <Assets.hpp>

using namespace std::chrono_literals;

class Engine 
{
public:
	Engine();

	bool isMouseOverSelectBar(sf::Vector2i pos);
	void Draw(sf::RenderWindow& window, sf::Vector2i pos);

	// RIGID BODY UI:
	void setBGColorRBUI(sf::Color color) { RBbutton.setFillColor(color); }
	void setBGColorRBsquare(sf::Color color) { RBselect1.setFillColor(color); }
	void setBGColorRBcircle(sf::Color color) { RBselect2.setFillColor(color); }
	void setBGColorRBreset(sf::Color color) { RBreset.setFillColor(color); }

	void setPosRBUI(sf::Vector2f pos);
	void setPosRBs(sf::Vector2f pos);

	bool isMouseOverRBUI(sf::Vector2i pos) { return RBbutton.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverRBsquare(sf::Vector2i pos) { return RBselect1.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverRBcircle(sf::Vector2i pos) { return RBselect2.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverRBreset(sf::Vector2i pos) { return RBreset.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverRBpanels(sf::Vector2i pos);

	bool isMouseClickedRBUI(sf::Vector2i pos);
	bool isMouseClickedRBsquare(sf::Vector2i pos);
	bool isMouseClickedRBcircle(sf::Vector2i pos);
	bool isMouseClickedRBreset(sf::Vector2i pos);

	void createRigidBodyPanel(sf::Vector2i pos);
	void setRBstatus(sf::Vector2i pos);

	bool isSpawnRBsquare(sf::Vector2i pos);
	bool isSpawnRBcircle(sf::Vector2i pos);
	/****************************************************/

	// PENDULUM UI:
	void setBGColorPENUI(sf::Color color) { PENbutton.setFillColor(color); }
	void setBGColorDPB(sf::Color color) { doublePendulumButton.setFillColor(color); }
	void setBGColorPB(sf::Color color) { pendulumButton.setFillColor(color); }
	void setBGColorPENreset(sf::Color color) { PENreset.setFillColor(color); }

	void setPosPENUI(sf::Vector2f pos);
	void setPosPENS(sf::Vector2f pos);

	bool isMouseOverPENUI(sf::Vector2i pos) { return PENbutton.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverDPB(sf::Vector2i pos) { return doublePendulumButton.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverPB(sf::Vector2i pos) { return pendulumButton.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverPENreset(sf::Vector2i pos) { return PENreset.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverPENpanel(sf::Vector2i pos);

	bool isMouseClickedPENUI(sf::Vector2i pos);
	bool isMouseClickedDPB(sf::Vector2i pos);
	bool isMouseClickedPB(sf::Vector2i pos);
	bool isMouseClickedPENreset(sf::Vector2i pos);

	void createPendulumPanel(sf::Vector2i pos);
	void setPENstatus(sf::Vector2i pos);

	bool isSpawnPendulum(sf::Vector2i pos);
	bool isSpawnDPendulum(sf::Vector2i pos);
	/****************************************************/

	// SOFTBODY UI:
	void setBGColorSBUI(sf::Color color) { SBbutton.setFillColor(color); }
	void setBGColorSBAB(sf::Color color) { SBAbutton.setFillColor(color); }
	void setBGColorSBreset(sf::Color color) { SBreset.setFillColor(color); }

	void setPosSBUI(sf::Vector2f pos);
	void setPosSB(sf::Vector2f pos);

	bool isMouseOverSBUI(sf::Vector2i pos) { return SBbutton.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverSBAB(sf::Vector2i pos) { return SBAbutton.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverSBreset(sf::Vector2i pos) { return SBreset.getGlobalBounds().contains((sf::Vector2f)pos); }
	bool isMouseOverSBpanel(sf::Vector2i pos) { return SBpanel.getGlobalBounds().contains((sf::Vector2f)pos); }

    bool isMouseClickedSBUI(sf::Vector2i pos);
	bool isMouseClickedSBAB(sf::Vector2i pos);
	bool isMouseClickedSBreset(sf::Vector2i pos);
	
	void createSoftbodyPanel(sf::Vector2i pos);
	void setSBstatus(sf::Vector2i pos);

	bool isSpawnSoftBody(sf::Vector2i pos);
	
	/****************************************************/
	sf::RectangleShape barSelect;
private:
	Objects objects;
	Assets assets;
private:
	bool toggled;
	bool toggled2;
	bool toggled3;

	bool disableRBpanel;
	bool disablePENpanel;
	bool disableSBpanel;

	sf::Texture texture;
	sf::Font font;

private:
	sf::RectangleShape RBbutton;
	sf::Text RBtxt;

	sf::RectangleShape RBselect1; // FOR SQUARE RIGID BODY
	sf::Text RBselectTxt;

	sf::RectangleShape RBselect2; // FOR CIRCLE RIGID BODY
	sf::Text RBselectTxt2;

	sf::RectangleShape RBreset; // RESET THE RIGID BODY'S STATUS
	sf::Text RBresetTxt;

	sf::Text RBinstructionsTxt;

	sf::RectangleShape RBpanel;
	sf::Text RBpanelTxt;

	sf::Text RBstatusTxt;
	std::string RBstatusOnOrOff;
	std::string RBstatusString;
	bool RBstatusBool;

	bool RBsquareActivate;
	bool RBcircleActivate;

	bool allowSquareToSpawn;
	bool allowCircleToSpawn;
private:
	sf::RectangleShape PENbutton;
	sf::Text PENtxt;

	sf::RectangleShape PENpanel;
	sf::Text PENpanelTxt;

	sf::RectangleShape doublePendulumButton;
	sf::Text doublePendulumTxt;

	sf::RectangleShape pendulumButton;
	sf::Text pendulumTxt;

	sf::RectangleShape PENreset;
	sf::Text PENresetTxt;

	sf::Text PENinstructionsTxt;

	sf::Text PENstatusTxt;
	std::string PENstatusOnOrOff;
	std::string PENstatusString;
	bool PENstatusBool;

	bool pendulumActivate;
	bool doublePendulumActivate;

	bool allowPendulumToSpawn;
	bool allowDoublePendulumToSpawn;
private:
	sf::RectangleShape SBbutton;
	sf::Text SBtxt;

	sf::RectangleShape SBpanel;
	sf::Text SBpanelTxt;

	sf::RectangleShape SBAbutton;
	sf::Text SBAtxt;

	sf::RectangleShape SBreset;
	sf::Text SBresetTxt;

	sf::Text SBinstructionsTxt;

	sf::Text SBstatusTxt;
	std::string SBstatusOnOrOff;
	std::string SBstatusString;
	bool SBstatusBool;

	bool softBodyActivate;
	bool allowSoftBodyToSpawn;
};