#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream>
#include <fstream>
#include "SFML-2.5.1/include/nlohmann/json.hpp"

using json = nlohmann::json;

class WorldMap
{
private:
	sf::FloatRect boss_entry;
	sf::FloatRect arena_entry;
	sf::FloatRect classic_entry;
protected:
	bool open;
	std::vector<sf::FloatRect> colliders;
	std::string ldtk_filename;
	json j;

	
public:
	WorldMap();
	virtual ~WorldMap();
	virtual void play(sf::RenderWindow& window, Player& player);
	virtual void set_players_spawn_point(Player& player);
	void bossScene(sf::RenderWindow& window, Player& player, std::string obj);
	virtual void update_player(sf::RenderWindow& window, Player& player);
};

