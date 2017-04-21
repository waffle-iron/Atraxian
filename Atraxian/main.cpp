#include <SFML\Graphics.hpp>

#include "Environment.hpp"
#include "logger.hpp"

#include <iostream>

int main()
{
	logger::INFO("Initlializing Atraxian " + ENVIRONMENT_VERSION + "...");

	Environment *atraxia = new Environment(sf::VideoMode(1080, 720), ("AtraxiaN-" + ENVIRONMENT_VERSION));
	atraxia->main();
	delete atraxia;

	logger::INFO("Exiting...");
	return 0;
}
