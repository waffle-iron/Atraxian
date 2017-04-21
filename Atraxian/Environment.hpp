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

	namespace filesystem
	{
		bool exists(std::string thing_that_may_or_may_not_be_real);

		void create_dir(std::string name, std::string dir);

		void create_file(std::string name, std::string extention, std::string dir);

		bool move(std::string from, std::string to);

		bool remove(std::string thing_to_remove);
	}
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
	Pane *nullPane;
	Pane *focusedPane = nullPane;
};

const std::string ENVIRONMENT_VERSION("0.0.59");

#endif 
