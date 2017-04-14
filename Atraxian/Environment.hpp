//----------------------------------
// PURPOSE: Holds all code used across the entire application;
// utilities such as getTime and other stuff that every part of the OS might need.
//----------------------------------

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics.hpp>

class Taskbar;
class Pane;

namespace environment
{
	std::string getTimestamp();
}

class Environment
{
public:
	Environment(sf::VideoMode dimensions, sf::String title);
	~Environment();

	sf::RenderWindow *window;
	Taskbar *taskbar;

	void main();
	void focusPane(Pane* pane);

private:
	std::vector<Pane*> panes;
	Pane *focusedPane;
};

#define ENVIRONMENT_VERSION "0.0.52"

#endif 
