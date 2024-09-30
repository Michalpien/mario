#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "player.h"
#include "PauseMenu.h"

class MainMenu : public PauseMenu
{

private:
	float x;
	float y;
	const int FRAME_DELAY = 200;
	int curentFrame;
	sf::Clock clock;
	sf::Time lastUpdate;
	sf::Texture first_icone_texture;
	sf::Texture second_icone_texture;
	sf::Texture name_texture;
	sf::Texture planet_texture;

	sf::Sprite planet_sprite;
	sf::Sprite name_sprite;
	sf::Sprite first_icone_sprite;
	sf::Sprite second_icone_sprite;

	sf::Texture first_icone_clicker;
	sf::Texture second_icone_clicker;
public:
	MainMenu();
	void draw(sf::RenderWindow& i_window, Player& player);
	void picking(sf::RenderWindow& i_window, Player& player);
};

