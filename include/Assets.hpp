#pragma once

#include <iostream> 

class Assets
{
public:
	void printPaths()
	{
		std::cout << "Background: " << BACKGROUND << "\n";
		std::cout << "Font: " << FONT << "\n";
		std::cout << "Music for Main Menu: " << MUSIC_FOR_MAIN_MENU << "\n";
		std::cout << "Music for Game Play: " << MUSIC_FOR_GAME_PLAY << "\n";
	}

public:
	std::string background = BACKGROUND;
	std::string font = FONT;
	std::string musicForMainMenu = MUSIC_FOR_MAIN_MENU;
	std::string musicForGamePlay = MUSIC_FOR_GAME_PLAY;
};
