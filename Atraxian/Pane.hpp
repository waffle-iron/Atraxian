#ifndef PANE_HPP
#define PANE_HPP

#include <SFML\Graphics.hpp>

class Pane
{
public:
	Pane(sf::Vector2f &size, int pid, sf::RenderWindow *window);
	~Pane();

	int PID; // Pane ID
	bool focused;
	bool active;

	void setPosition(sf::Vector2f &newpos);
	void focus();
	void defocus();

	sf::RectangleShape mainpane;
	sf::RectangleShape titlebar;
	sf::RectangleShape closebutton;
	sf::RectangleShape leftborder;
	sf::RectangleShape rightborder;
	sf::RectangleShape bottomborder;

private:
	sf::RenderWindow *window;
};

#endif