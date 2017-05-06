#ifndef PANE_HPP
#define PANE_HPP

#include "Environment.hpp"

#include <SFML\Graphics.hpp>
#include <vector>

class Pane
{
public:
	Pane(const sf::Vector2f size, const std::string title, const int pid, Environment *env);
	~Pane();

	sf::RectangleShape mainpane;
	sf::RectangleShape titlebar;
	sf::RectangleShape closebutton;
	sf::RectangleShape leftborder;
	sf::RectangleShape rightborder;
	sf::RectangleShape bottomborder;
	sf::RectangleShape boundingbox;
	sf::Text titletext;

	int PID; // Pane ID
	bool focused;
	bool active;
	bool visible;

	void setPosition(const sf::Vector2f newpos);
	void setTitle(const std::string title);
	void resize(const sf::Vector2f newsize);
	void focus();
	void defocus();

	std::vector<sf::Drawable*> pane_content;

private:
	Environment *environment;
	sf::Font font;
	
	void setSize(const sf::Vector2f size);
};

#endif /* PANE_HPP */