#include "player.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#define speed 0.7

Player::Player() : name("luigi"), name_2("mario"), x(128), y(120), first_character(false), NUM_FRAMES(1), line(1), CHARACTER_HIGHT(10), direction(0)
{
	texture.loadFromFile("images/luigi_sheet.png");
	y_speed = 0;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
	can_jump = true;
}


void Player::set_poz(float x_p, float y_p)
{
	x = x_p;
	y = y_p;
}

int Player::get_x()
{
	return x;
}

int Player::get_y()
{
	return y;
}

void Player::draw(sf::RenderWindow& i_window)
{
	sprite.setPosition(round(x), round(y));
	i_window.draw(sprite);
}

// player moving in x axis and animate
void Player::left_right()
{
	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = 1;
		if (can_jump)
		{
			currentFrame = (currentFrame + 1) % (NUM_FRAMES * 8);
			if (NUM_FRAMES != 1)
				sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction * 2 + 1 - (currentFrame / 8)), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
			else
				sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction + currentFrame / 8), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		x -= speed;
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = 0;
		if (can_jump)
		{
			currentFrame = (currentFrame + 1) % (NUM_FRAMES * 8);
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction + currentFrame / 8), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		x += speed;
	}
	else
	{
		if (NUM_FRAMES != 1 && direction == 1)
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction * 2 + 1 ), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		else
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
	}
}

// player moving in y axis and animate
void Player::up_down()
{
	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (direction == 1) {
			currentFrame = (currentFrame + 1) % (NUM_FRAMES * 8);
			if (NUM_FRAMES != 1)
				sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction * 2 + 1 - (currentFrame / 8)), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
			else
				sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction + currentFrame / 8), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		else {
			currentFrame = (currentFrame + 1) % (NUM_FRAMES * 8);
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction + currentFrame / 8), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		y -= speed;
	}
	else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (direction == 1) {
			currentFrame = (currentFrame + 1) % (NUM_FRAMES * 8);
			if (NUM_FRAMES != 1)
				sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction * 2 + 1 - (currentFrame / 8)), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
			else
				sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction + currentFrame / 8), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		else {
			currentFrame = (currentFrame + 1) % (NUM_FRAMES * 8);
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction + currentFrame / 8), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		y += speed;
	}
	/*else
	{
		if (NUM_FRAMES != 1 && direction == 1)
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction * 2 + 1), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		else
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * (NUM_FRAMES * direction), FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
	}*/
}


void Player::jump()
{
	if (can_jump)
	{
		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			y_speed = -2;
			can_jump = false;
		}
	}
	else
	{
		if (direction == 1) {
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * 5, FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		else {
			sprite.setTextureRect(sf::IntRect(FRAME_WIDTH * 4, FRAME_WIDTH * line, CHARACTER_HIGHT, CHARACTER_HIGHT));
		}
		
	}
}

void Player::gravitation()
{
	y += y_speed;
	y_speed += 0.035;
}

void Player::stop_y()
{
	y_speed = 0;
}

sf::FloatRect Player::getPlayerCollider()
{
	return sprite.getGlobalBounds();
}

// stepping back if hit wall
void Player::step_back(bool left, bool right, bool up, bool down)
{
	if (left) { x += speed; }
	if (right) { x -= speed; }
	if (up) { y -= speed; }
	if (down) { y += speed; }

}

// changin character
void Player::change_look(std::string file_name)
{

	if (!texture.loadFromFile(file_name))
	{
		std::cout << "Error with loading player look";
	}


	sprite.setTexture(texture);
}

void Player::set_line(int new_line) {
	line = new_line;
}

void Player::set_height(int new_height) {
	CHARACTER_HIGHT = new_height;
}

void Player::set_frames(int new_frames) {
	NUM_FRAMES = new_frames;
}

void Player::let_jump(bool let)
{
	can_jump = let;
}

void Player::change_direction(bool new_direction)
{
	direction = new_direction;
}