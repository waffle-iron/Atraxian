#ifndef PANE_HPP
#define PANE_HPP

#include <SFML\Graphics.hpp>

class Pane
{
public:
	Pane(const sf::Vector2f size, int pid, sf::RenderWindow *window);
	~Pane();

	sf::RectangleShape mainpane;
	sf::RectangleShape titlebar;
	sf::RectangleShape closebutton;
	sf::RectangleShape leftborder;
	sf::RectangleShape rightborder;
	sf::RectangleShape bottomborder;
	sf::RectangleShape boundingbox;

	int PID; // Pane ID
	bool focused;
	bool active;

	void setPosition(const sf::Vector2f newpos);
	void focus();
	void defocus();

private:
	sf::RenderWindow *window;
};

#endif