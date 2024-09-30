#pragma once
#include "Player_Fight.h"

class Fight
{
private:
	bool turn;
	bool end;
	bool sk;
	sf::Texture background_texture;
	sf::Texture characters_texture;
	sf::Texture entry_texture;
	sf::Texture skilsb_texture;
	sf::Texture text_texture;
	sf::Sprite text_sprite;
	sf::Sprite skilsb_sprite;
	sf::Sprite entry_sprite;
	sf::Sprite characters_sprite;
	sf::Sprite background_sprite;
	sf::Text text;
	sf::Font font;
public:
	Fight(std::string pl);
	void draw(sf::RenderWindow& window, PlayerFight& player, Boss& boss);
	void displayText(sf::RenderWindow& window, PlayerFight& player, Boss& boss, std::string full_text);
	void play_entry(sf::RenderWindow& window);
	void display_background(sf::RenderWindow& window);
	void play_skill_animation(sf::RenderWindow& window, PlayerFight& player, Boss& boss, Skill& skill);
	void fight(sf::RenderWindow& window, PlayerFight& player, Boss& boss);
};

