#include "MainMenu.h"
#include <SFML/Window/Mouse.hpp>
#include "WorldMap.h"
#include <chrono>
#include <thread>


MainMenu::MainMenu() : x(128), y(120), curentFrame(0)
{

	start_texture.loadFromFile("images/start_button.png");
	options_texture.loadFromFile("images/option_button.png");
	background_texture.loadFromFile("images/background.png");
	first_icone_texture.loadFromFile("images/luigi_icone.png");
	second_icone_texture.loadFromFile("images/mario_icone.png");
	first_icone_clicker.loadFromFile("images/luigi_icone_c.png");
	second_icone_clicker.loadFromFile("images/mario_icone_c.png");
	name_texture.loadFromFile("images/name.png");
	planet_texture.loadFromFile("images/planet.png");

	planet_sprite.setTexture(planet_texture);
	name_sprite.setTexture(name_texture);
	background_sprite.setTexture(background_texture);
	start_sprite.setTexture(start_texture);
	options_sprite.setTexture(options_texture);
	first_icone_sprite.setTexture(first_icone_clicker);
	second_icone_sprite.setTexture(second_icone_texture);

	planet_sprite.setPosition(53, 45);
	first_icone_sprite.setPosition(round(x - 24), round(y + 32));
	second_icone_sprite.setPosition(round(x + 4), round(y + 32));

	lastUpdate = clock.getElapsedTime();
}

void MainMenu::draw(sf::RenderWindow& i_window, Player& player)
{
	PauseMenu::draw_background(i_window);

	sf::Time elapsed = clock.getElapsedTime() - lastUpdate;
	if (elapsed.asMilliseconds() >= FRAME_DELAY) {
		curentFrame = (curentFrame + 1) % 100;
		planet_sprite.setTextureRect(sf::IntRect(curentFrame * 150, 0, 150, 150));

		lastUpdate = clock.getElapsedTime();
	}
	i_window.draw(planet_sprite);
	i_window.draw(name_sprite);
	PauseMenu::draw(i_window);
	i_window.draw(first_icone_sprite);
	i_window.draw(second_icone_sprite);
}

void MainMenu::picking(sf::RenderWindow& window, Player& player)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::FloatRect start_bounds = start_sprite.getGlobalBounds();
		sf::FloatRect options_bounds = options_sprite.getGlobalBounds();
		sf::FloatRect first_icone_bounds = first_icone_sprite.getGlobalBounds();
		sf::FloatRect second_icone_bounds = second_icone_sprite.getGlobalBounds();

		if (start_bounds.contains(mouse))
		{
			WorldMap w_map;
			w_map.play(window, player);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		else if (options_bounds.contains(mouse))
		{
			window.close();
		}
		else if (first_icone_bounds.contains(mouse))
		{
			first_icone_sprite.setTexture(first_icone_clicker);
			second_icone_sprite.setTexture(second_icone_texture);
			player.change_look("images/luigi_sheet.png");
			player.name = "luigi";
			player.name_2 = "mario";
			player.first_character = true;

		}
		else if (second_icone_bounds.contains(mouse))
		{
			first_icone_sprite.setTexture(first_icone_texture);
			second_icone_sprite.setTexture(second_icone_clicker);
			player.change_look("images/mario_sheet.png");
			player.name = "mario";
			player.name_2 = "luigi";
			player.first_character = false;
		}
	}
}
