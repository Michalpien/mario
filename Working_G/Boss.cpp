#include "Boss.h"
#include <chrono>
#include <random>

Boss::Boss(std::string n, int health) : name(n), health(health), maxHealth(health), shield(false), currentFrame(0)
{
	name[0] = toupper(name[0]);
	health_texture.loadFromFile("images/health.png");
	health_sprite.setTexture(health_texture);
	health_sprite.setTextureRect(sf::IntRect(80 * currentFrame, 0, 80, 24));
	font.loadFromFile("assets/pixText.ttf");
	text.setFont(font);
	text.setString(name + "\t" + std::to_string(health) + "/" + std::to_string(maxHealth));
	text.setCharacterSize(24);
	text.setScale(0.25f, 0.25f);
	text.setFillColor(sf::Color::Black);
	//std::unique_ptr<Skill> added_atack = std::make_unique<Skill>("", "", "", 0, 0, 0, 0);
	//skils.push_back(std::move(added_atack));
}

std::string Boss::getName()
{
	return name;
}

void Boss::receiveDamage(int damage)
{
	if (!shield and damage > 0) { health = (damage >= health)? 0 : health - damage; currentFrame = (health <= 0) ? 10 : 10 - (health % 100) / 10;
	}
	else { shield = false; }
	health_sprite.setTextureRect(sf::IntRect(80 * currentFrame, 0, 80, 24));
	text.setString(name + "\t" + std::to_string(health) + "/" + std::to_string(maxHealth));
}

void Boss::setShield(bool sh)
{
	shield = sh;
}

void Boss::addAtack(std::string name, std::string icone, std::string animation, int frames, int size, float x, float y, int damage, bool shield)
{
	std::unique_ptr<Skill> added_atack = std::make_unique<Skill>(name, icone, animation, frames, size, x, y, damage, shield);
	skils.push_back(std::move(added_atack));
}

Skill& Boss::useSkill()
{
	auto& skill = skils[chooseAtack()+1];
	return *skill;
}



int Boss::chooseAtack()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::mt19937 generator(seed); 
	return generator() % (skils.size() );
}

void Boss::draw_health(sf::RenderWindow& window)
{
	window.draw(health_sprite);
	window.draw(text);
}

void Boss::set_poz(float e_x, float e_y, float s_x, float s_y, float h_x, float h_y)
{
	health_sprite.setPosition(h_x, h_y);
	text.setPosition(h_x + 20, h_y + 5);
	for (auto& skill : skils)
	{
		skill->set_self_poz(s_x, s_y);
		skill->set_animation_poz(e_x, e_y);
	}
}

