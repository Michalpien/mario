#include "Fight.h"
#include <chrono>
#include <thread>
#include <iostream>

Fight::Fight(std::string pl) : turn(true), end(false), sk(false)
{
	background_texture.loadFromFile("images/background_f.png");
	entry_texture.loadFromFile("images/entry.png");
	characters_texture.loadFromFile("images/"+pl+"_fight.png");
	text_texture.loadFromFile("images/text_b.png");
	skilsb_texture.loadFromFile("images/skill_b.png");

	skilsb_sprite.setTexture(skilsb_texture);
	text_sprite.setTexture(text_texture);
	background_sprite.setTexture(background_texture);
	entry_sprite.setTexture(entry_texture);
	characters_sprite.setTexture(characters_texture);
	font.loadFromFile("assets/pixText.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setScale(0.15f, 0.15f);
	text.setFillColor(sf::Color::White);
	text.setPosition(15, 225);
	skilsb_sprite.setPosition(168, 192);
	text_sprite.setPosition(3, 213);
}

void Fight::draw(sf::RenderWindow& window, PlayerFight& player, Boss& boss)
{
	window.clear();
	display_background(window);
	window.draw(skilsb_sprite);
	window.draw(text_sprite);
	player.draw_health(window);
	boss.draw_health(window);
	player.displaySkils(window);
	window.display();
}

void Fight::displayText(sf::RenderWindow& window, PlayerFight& player, Boss& boss, std::string full_text)
{
	draw(window, player, boss);
	std::string delay = "";
	for (int i = 0; i < full_text.length(); i++)
	{
		delay += full_text[i];
		text.setString(delay);
		window.draw(text);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
	while (1 != sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && window.isOpen());
}


void Fight::play_entry(sf::RenderWindow& window)
{
	for (int i = 0; i < 19; i++)
	{
		window.clear();
		display_background(window);
		entry_sprite.setTextureRect(sf::IntRect(256 * i, 0, 256, 240));
		window.draw(entry_sprite);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void Fight::display_background(sf::RenderWindow& window)
{
	window.draw(background_sprite);
	window.draw(characters_sprite);
}

void Fight::play_skill_animation(sf::RenderWindow& window, PlayerFight& player, Boss& boss, Skill& skill)
{
	while (window.isOpen() && skill.isPlaying())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		display_background(window);
		skill.play_animation(window);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	skill.restart();
}



void Fight::fight(sf::RenderWindow& window, PlayerFight& player, Boss& boss)
{
	play_entry(window);
	while (window.isOpen() && !end)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		draw(window, player, boss);
		if (player.health <= 0) { displayText(window, player, boss, "Congratulations, you lost!!!"); end = true; }
		else if (boss.health <= 0) { displayText(window, player, boss, "Congratulations, you won!!!"); end = true; }

		else if (turn) {
			Skill& skill = player.chooseAtack(window, turn, end, sk);
			if (sk)
			{
				displayText(window, player, boss, player.getName() + " used "  + skill.getName() + "....");
				play_skill_animation(window, player, boss, skill);
			
				boss.receiveDamage(skill.getDamage());
				player.setShield(skill.getShield());
		}
			
		}
		else
		{
			turn = true;
			Skill& skill = boss.useSkill();
			displayText(window, player, boss, boss.getName() + " used " + skill.getName() + "....");
			play_skill_animation(window, player, boss, skill);
			player.receiveDamage(skill.getDamage());
			boss.setShield(skill.getShield());
		}
	}
}
