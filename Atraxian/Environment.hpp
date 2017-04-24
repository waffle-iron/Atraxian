//----------------------------------
// PURPOSE: Holds all code used across the entire application;
// utilities such as getTime and other stuff that every part of the OS might need.
//----------------------------------

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics.hpp>

class Renderer;
class Taskbar;
class Pane;

namespace environment
{
	std::string getTimestamp();
}

class Environment
{
public:
	Environment(sf::VideoMode dimensions, std::string title);
	~Environment();

	sf::RenderWindow *window;
	Taskbar *taskbar;

	void main();
	void focusPane(Pane* pane);

private:
	std::vector<Pane*> panes;
	Pane *nullPane;
	Pane *focusedPane = nullPane;
};

const std::string ENVIRONMENT_VERSION("0.0.62");

#endif 
