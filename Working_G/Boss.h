#pragma once
#include <SFML/Graphics.hpp>
#include "Skill.h"
#include "player.h"

class Boss
{
protected:
	int currentFrame;
	int maxHealth;
	bool shield;

	std::string name;
	std::vector<std::unique_ptr<Skill>> skils;
	sf::Texture health_texture;
	sf::Sprite health_sprite;
	sf::Text text;
	sf::Font font;

public:
	int health;
	Boss(std::string n, int health);
	std::string getName();
	void receiveDamage(int damage);
	void setShield(bool sh);
	void addAtack(std::string name, std::string icone, std::string animation, int frames, int size, float x, float y, int damage = 0, bool shield = false);
	virtual Skill& useSkill();
	virtual int chooseAtack();
	void draw_health(sf::RenderWindow& window);
	void set_poz(float e_x, float e_y, float h_x, float h_y, float s_x, float s_y);
};

