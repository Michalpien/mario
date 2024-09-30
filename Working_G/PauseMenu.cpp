#include "PauseMenu.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "iostream"

PauseMenu::PauseMenu() : x(128), y(120), ret(false), close(false)
{

	start_texture.loadFromFile("images/reset_button.png");
	options_texture.loadFromFile("images/return_button.png");
	background_texture.loadFromFile("images/background_p_m.png");

	background_sprite.setTexture(background_texture);
	start_sprite.setTexture(start_texture);
	options_sprite.setTexture(options_texture);

}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw(sf::RenderWindow& i_window)
{
	start_sprite.setPosition(round(x - 24), round(y - 16));
	options_sprite.setPosition(round(x - 24), round(y + 8));

	
	i_window.draw(start_sprite);
	i_window.draw(options_sprite);

}

void PauseMenu::draw_background(sf::RenderWindow& i_window)
{
	i_window.draw(background_sprite);
}

void PauseMenu::picking(sf::RenderWindow& window, Player& player)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::FloatRect start_bounds = start_sprite.getGlobalBounds();
		sf::FloatRect options_bounds = options_sprite.getGlobalBounds();


		if (start_bounds.contains(mouse))
		{
			close = true;
		}
		else if (options_bounds.contains(mouse))
		{
			ret = true;
			close = true;
		}
	}
}

void PauseMenu::display(sf::RenderWindow& i_window, Player& player)
{

	while (i_window.isOpen() && !close)
	{
		sf::Event event;
		while (i_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				i_window.close();
		}
		picking(i_window, player);
		draw_background(i_window);
		draw(i_window);
		i_window.display();
	}
}

void PauseMenu::restart()
{
	close = false;
}
