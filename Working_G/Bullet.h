#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
class Bullet
{
private:
	double x;
	double y;
	double x_s;
	double y_s;
	sf::Vector2f m;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Bullet(int x, int y, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& i_window);
	sf::FloatRect getCollider();
};

