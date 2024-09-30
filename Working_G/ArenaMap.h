#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream>
#include <fstream>
#include "SFML-2.5.1/include/nlohmann/json.hpp"
#include "WorldMap.h"
#include "Enemy.h"
#include "Bullet.h"

using json = nlohmann::json;

class ArenaMap : public WorldMap
{
private:
	bool end;
	std::vector<Enemy> enemies;
	std::vector <Bullet> bullets;
	sf::Time lastUpdate;
	sf::Time lastSpawn;
	sf::Clock clock;
	int counter;
public:
	ArenaMap();
	void play(sf::RenderWindow& window, Player& player);
	void set_players_spawn_point(Player& player);
	void update_player(sf::RenderWindow& window, Player& player);
	void update_enemies(sf::RenderWindow& window, Player& player);
	void update_bullets(sf::RenderWindow& window, Player& player);
	void draw_items(sf::RenderWindow& window);
};

