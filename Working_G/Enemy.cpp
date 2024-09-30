#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y)
{
    this->x = x;
    this->y = y;
    direction = 0;
    texture.loadFromFile("images/goomba.png");
    sprite.setScale(0.016f, 0.016f);
    sprite.setTexture(texture);
}

// moving emeny toward player
void Enemy::update(Player& player)
{
    if (player.get_x() + 3 > this -> x)
    {
        x += 0.5;
    }
    else if (player.get_x() + 3 < this->x)
    {
        x -= 0.5;
    }
    if (player.get_y() + 6 > this->y)
    {
        y += 0.5;
    }
    else if (player.get_y() +  6 < this->y)
    {
        y -= 0.5;
    }
}

void Enemy::walk()
{
    if (direction)
        x += 0.5;
    else
        x -= 0.5;
}

void Enemy::change_direction()
{
    direction = !direction;
}

// drawing enemy
void Enemy::draw(sf::RenderWindow& i_window)
{
    sprite.setPosition(round(x), round(y));
    sprite.setTexture(texture);
    i_window.draw(sprite);
}

// getting enemy collidor
sf::FloatRect Enemy::getCollider()
{
    return sprite.getGlobalBounds();
}