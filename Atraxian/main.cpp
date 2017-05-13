#include "Environment.hpp"
#include "Logger.hpp"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFBASH\Console.hpp>

#include <iostream>
#include <thread>

void new_Env(int envID)
{
	Environment *atraxian = new Environment(sf::VideoMode(1080, 720), ("AtraxiaN-" + ENVIRONMENT_VERSION), envID);
	atraxian->main();
	delete atraxian;
}

void new_Con(int conID)
{
	Console *console = new Console("Terminal");
	console->create();
	delete console;
}

int main()
{
	logger::INFO("Initlializing Atraxian " + ENVIRONMENT_VERSION + "...");
	logger::BREAK();

	std::thread one_env(new_Env, 1);
//	std::thread one_con(new_Con, 1);
	one_env.join();
//	one_con.join();

	logger::INFO("Exiting...");
	return 0;
}
