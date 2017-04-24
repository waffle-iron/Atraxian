#include <SFML\Graphics.hpp>

#include "Environment.hpp"
#include "Logger.hpp"

#include <iostream>

int main()
{
	logger::INFO("Initlializing Atraxian " + ENVIRONMENT_VERSION + "...");
	logger::BREAK();

	Environment *atraxian = new Environment(sf::VideoMode(1080, 720), ("AtraxiaN-" + ENVIRONMENT_VERSION));
	atraxian->main();
	delete atraxian;

	logger::INFO("Exiting...");
	return 0;
}
