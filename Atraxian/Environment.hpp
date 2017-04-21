//----------------------------------
// PURPOSE: Holds all code used across the entire application;
// utilities such as getTime and other stuff that every part of the OS might need.
//----------------------------------

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <experimental\filesystem>
#include <fstream>
#include <iostream>

class Renderer;
class Taskbar;
class Pane;

namespace fs = std::experimental::filesystem;

namespace environment
{
	std::string getTimestamp();

	namespace filesystem
	{
		void create_dir(std::string name, std::string dir);

		void create_file(std::string name, std::string ext, std::string dir);

		bool exists(std::string thing_that_may_or_may_not_be_real); // yus

		void move(std::string from, std::string to);

		void remove_dir(std::string name, std::string dir);

		void remove_file(std::string file, std::string dir);
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
