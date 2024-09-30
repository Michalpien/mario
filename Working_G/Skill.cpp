#include "Skill.h"

Skill::Skill(std::string name, std::string icone, std::string animation, int frames, int size, float x, float y, int damage, bool shield) : 
	name(name), frames(frames), size(size), damage(damage), shield(shield)
{
	icone_texture.loadFromFile(icone);
	animation_texture.loadFromFile(animation);

	animation_sprite.setTexture(animation_texture);
	icone_sprite.setTexture(icone_texture);
	icone_sprite.setPosition(x, y);
}

bool Skill::getShield()
{
	return shield;
}

int Skill::getDamage()
{
	return damage;
}

std::string Skill::getName()
{
	return name;
}

void Skill::set_animation_poz(float x, float y)
{
	x -= size / 2;
	y -= size / 2;
	if (!shield) {
		animation_sprite.setPosition(x, y);
	}
	else{ animation_sprite.setPosition(s_x, s_y); }
	
}


void Skill::play_animation(sf::RenderWindow& window)
{
	currentFrame = (currentFrame + 1) % frames;
	animation_sprite.setTextureRect(sf::IntRect(size * currentFrame, 0, size, size));
	window.draw(animation_sprite);
}

void Skill::display_icone(sf::RenderWindow& window)
{
	window.draw(icone_sprite);
}

bool Skill::isPlaying()
{
	if (currentFrame + 1 >= frames) { return false; }
	return true;
}

sf::FloatRect Skill::skill_border()
{
	return icone_sprite.getGlobalBounds();
}

void Skill::set_self_poz(float x, float y)
{
	s_x = x - size / 2 + 10;
	s_y = y - size / 2;
}

void Skill::restart()
{
	currentFrame = 0;
}
