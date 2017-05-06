#ifndef TASKBAR_HPP
#define TASKBAR_HPP

#include <SFML\Graphics.hpp>

class Environment;

class Taskbar
{
public:
	Taskbar(Environment *environment);
	~Taskbar();

	sf::RectangleShape bar;
	sf::RectangleShape start_button;
	sf::RectangleShape div;
//	sf::Text time;

	bool is_start_open;
	bool is_hidden;

	void open_start_menu();
	void close_start_menu();

private:
	Environment *environment;
//	sf::Font font;
};

#endif /* TASKBAR_HPP */