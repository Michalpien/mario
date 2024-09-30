#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>


class Player
{
private:

	float x;
	float y;
	double y_speed;
	const int FRAME_WIDTH = 16;
	const int FRAME_HEIGHT = 16;
	int CHARACTER_HIGHT;
	int NUM_FRAMES;
	int line;
	int currentFrame = 0;
	bool direction;
	sf::Sprite sprite;
	bool can_jump;
	sf::Texture texture;


public:
	Player();
	void change_direction(bool new_directionw);
	bool first_character;
	std::string name;
	std::string name_2;
	void set_poz(float x_p, float y_p);
	void draw(sf::RenderWindow& i_window);
	//void update();
	void left_right();
	void up_down();
	sf::FloatRect getPlayerCollider();
	void step_back(bool left = false, bool right = false, bool up = false, bool down = false);
	void change_look(std::string file_name);
	void set_line(int new_line);
	void set_height(int new_height);
	void set_frames(int new_frames);
	void jump();
	void gravitation();
	int get_x();
	int get_y();
	void stop_y();
	void let_jump(bool let);
};

