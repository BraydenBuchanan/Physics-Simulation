#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <Assets.hpp>

class MainMenu
{
public:
	MainMenu(const std::string& playTxt, const std::string& exitTxt, const std::string& mainTxt);

	void setBGColorPlayButton(sf::Color color) { playButton.setFillColor(color); }
	void setBGColorExitButton(sf::Color color) { exitButton.setFillColor(color); }

	void Draw(sf::RenderWindow& window);

	void setPos(sf::Vector2f pos);

	bool isMouseOverPlayButton(sf::Vector2i pos);
	bool isMouseOverExitButton(sf::Vector2i pos);

	bool isMouseClickedPlayButton(sf::Vector2i pos);
	bool isMouseClickedExitButton(sf::Vector2i pos);
private:
	Assets assets;

	sf::RectangleShape playButton;
	sf::Text playTxt;

	sf::RectangleShape exitButton;
	sf::Text exitTxt;

	sf::Text mainTxt;

	sf::Font font;

	sf::Sprite background;
	sf::Texture texture;
};