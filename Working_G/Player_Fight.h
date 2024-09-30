#pragma once
#include "Boss.h"
class PlayerFight :
    public Boss
{
private:
    sf::Texture run_texture;
    sf::Sprite run_sprite;
public:
    PlayerFight(std::string name, int health);
    Skill& chooseAtack(sf::RenderWindow& window, bool& turn, bool& end, bool& sk);
    void displaySkils(sf::RenderWindow& window);
};

