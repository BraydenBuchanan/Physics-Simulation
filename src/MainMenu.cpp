#include <MainMenu.hpp>

MainMenu::MainMenu(const std::string& playTxt, const std::string& exitTxt, const std::string& mainTxt) 
{
	
	if (!font.loadFromFile(assets.font))
		std::cerr << "Error loading font.\n";
	
	if (!texture.loadFromFile(assets.background))
		std::cerr << "Error loading background texture.\n";

	this->playTxt.setFont(font);
	this->playTxt.setString(playTxt);
	this->playTxt.setCharacterSize(20.f);
	this->playTxt.setFillColor(sf::Color::Black);

	this->exitTxt.setFont(font);
	this->exitTxt.setString(exitTxt);
	this->exitTxt.setCharacterSize(20.f);
	this->exitTxt.setFillColor(sf::Color::Black);

	this->mainTxt.setFont(font);
	this->mainTxt.setString(mainTxt);
	this->mainTxt.setCharacterSize(70.f);
	this->mainTxt.setFillColor(sf::Color::White);
	this->mainTxt.setPosition(220.f, 150.f);

	playButton.setSize(sf::Vector2f(150.f, 50.f));
	playButton.setOutlineThickness(3.f);
	playButton.setOutlineColor(sf::Color::Black);

	exitButton.setSize(sf::Vector2f(150.f, 50.f));
	exitButton.setOutlineThickness(3.f);
	exitButton.setOutlineColor(sf::Color::Black);

	background.setTexture(texture);
}

void MainMenu::setPos(sf::Vector2f pos)
{
	playButton.setPosition(pos.x, pos.y);

	playTxt.setPosition(playButton.getPosition().x + (playButton.getSize().x - playTxt.getLocalBounds().width) / 2.f,
		playButton.getPosition().y + (playButton.getSize().y - playTxt.getLocalBounds().height) / 2.5f);

	exitButton.setPosition(pos.x, pos.y + 70.f);

	exitTxt.setPosition(exitButton.getPosition().x + (exitButton.getSize().x - exitTxt.getLocalBounds().width) / 2.f,
		exitButton.getPosition().y + (exitButton.getSize().y - exitTxt.getLocalBounds().height) / 2.5f);
}

bool MainMenu::isMouseOverPlayButton(sf::Vector2i pos)
{
	return playButton.getGlobalBounds().contains((sf::Vector2f)pos);
}

bool MainMenu::isMouseOverExitButton(sf::Vector2i pos)
{
	return exitButton.getGlobalBounds().contains((sf::Vector2f)pos);
}

bool MainMenu::isMouseClickedPlayButton(sf::Vector2i pos)
{
	if (isMouseOverPlayButton({ pos.x, pos.y }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

bool MainMenu::isMouseClickedExitButton(sf::Vector2i pos)
{
	if (isMouseOverExitButton({ pos.x, pos.y }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	window.draw(background);

	window.draw(playButton);
	window.draw(playTxt);

	window.draw(exitButton);
	window.draw(exitTxt);
    window.draw(mainTxt);
}

