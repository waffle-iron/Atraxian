//----------------------------------
// PURPOSE: Holds all code that is used across the entire application;
// utilities such as getTime and other stuff that every part of the OS might need.
//----------------------------------

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics.hpp>

#include <string>

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

	void main();
};

#define ENVIRONMENT_VERSION "0.0.2"

#endif 
