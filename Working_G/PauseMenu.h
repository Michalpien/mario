#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "player.h"

class PauseMenu 
{
private:

	bool close;
protected:

	float x;
	float y;

	sf::Sprite start_sprite;
	sf::Sprite options_sprite;
	sf::Sprite background_sprite;
	sf::Texture background_texture;
	sf::Texture start_texture;
	sf::Texture options_texture;
public:
	bool ret;
    PauseMenu();
	virtual ~PauseMenu();
	void draw(sf::RenderWindow& i_window);
	void draw_background(sf::RenderWindow& i_window);
	virtual void picking(sf::RenderWindow& i_window, Player& player);
	virtual void display(sf::RenderWindow& i_window, Player& player);
	virtual void restart();
};

