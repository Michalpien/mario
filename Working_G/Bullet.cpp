#include "Bullet.h"
#include <SFML/Window/Mouse.hpp>


Bullet::Bullet(int x, int y, sf::RenderWindow& window) : x(x), y(y), x_s(x), y_s(y)
{
	m = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	texture.loadFromFile("images/ball.png");
	sprite.setTexture(texture);
	sprite.setScale(0.03f, 0.03f);
}

// shootinh bullet towards mouse
void Bullet::update(sf::RenderWindow& window)
{
	if (m.x > x_s + 16)
	{
		x += 1;
	}
	else if (m.x < x_s)
	{
		x -= 1;
	}

	if (m.y > y_s + 16)
	{
		y += 1;
	}
	else if (m.y < y_s)
	{
		y -= 1;
	}
	if (m.x <= x_s + 16 && m.x >= x_s && m.y <= y_s + 16 && m.y >= y_s) {
		x += 1;
	}
}

// moving bullet
void Bullet::draw(sf::RenderWindow& i_window)
{
	sprite.setPosition(round(x), round(y));
	sprite.setTexture(texture);
	i_window.draw(sprite);
}

// getting bullet collider
sf::FloatRect Bullet::getCollider()
{
	return sprite.getGlobalBounds();
}
