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
};

#endif