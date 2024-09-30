#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "player.h"
class Enemy
{
private:
	double x;
	double y;
	sf::Sprite sprite;
	sf::Texture texture;
	bool direction;
public:
	Enemy(int x, int y);
	void update(Player& player);
	void walk();
	void draw(sf::RenderWindow& i_window);
	sf::FloatRect getCollider();
	void change_direction();
};

