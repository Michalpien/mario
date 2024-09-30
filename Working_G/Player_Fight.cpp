#include "Player_Fight.h"
#include <iostream>

PlayerFight::PlayerFight(std::string name, int health) :
    Boss(name, health)
{
    run_texture.loadFromFile("images/Skils/run.png");
    run_sprite.setTexture(run_texture);
    run_sprite.setPosition(224, 218);

}

Skill& PlayerFight::chooseAtack(sf::RenderWindow& window, bool& turn, bool& end, bool& sk)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if (run_sprite.getGlobalBounds().contains(mouse))
		{
			end = true;
		}

		for (auto& skill : skils)
		{
			if(skill->skill_border().contains(mouse))
			{
				turn = false;
				sk = true;
				return *skill;
			}
		}
	}
	sk = false;
	auto& a = skils[0];
	return *a;
}

void PlayerFight::displaySkils(sf::RenderWindow& window)
{
    for (auto& skill : skils)
    {
        skill->display_icone(window);
    }
    window.draw(run_sprite);
}

