#ifndef PANE_HPP
#define PANE_HPP

#include <SFML\Graphics.hpp>

class Pane
{
public:
	Pane(sf::Vector2f &size, int pid);
	~Pane();

	int PID; // Pane ID
	bool focused;
	bool active;

	sf::RectangleShape mainpane;

	void setPosition(sf::Vector2f &newpos);
};

#endif