#pragma once
#include <SFML/Graphics.hpp>

class Skill
{
private:
	int frames;
	int size;
	int currentFrame = 0;
	int damage;
	bool shield;
	float s_x;	//user pozition
	float s_y;	//user pozition
	std::string name;
	sf::Texture icone_texture;
	sf::Texture animation_texture;
	sf::Sprite animation_sprite;
	sf::Sprite icone_sprite;
public:
	Skill(std::string name, std::string icone, std::string animation, int frames, int size, float x, float y, int damage=0, bool shield=false);
	bool getShield();
	int getDamage();
	std::string getName();
	void set_animation_poz(float x, float y);
	void play_animation(sf::RenderWindow& window);
	void display_icone(sf::RenderWindow& window);
	bool isPlaying();
	sf::FloatRect skill_border();
	void set_self_poz(float x, float y);
	void restart();
};

