#ifndef TASKBAR_HPP
#define TASKBAR_HPP

#include <SFML\Graphics.hpp>

class Taskbar
{
public:
	Taskbar(sf::RenderWindow *window);
	~Taskbar();

	sf::RectangleShape bar;
	sf::RectangleShape start_button;
	sf::RectangleShape div;

	bool is_start_open;

	void open_start_menu();
	void close_start_menu();
};

#endif