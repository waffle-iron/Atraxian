#include "Pane.hpp"
#include "Environment.hpp"
#include "logger.hpp"

Pane::Pane(sf::Vector2f &size, int pid)
{
	PID = pid;

	mainpane.setFillColor(sf::Color::Magenta);
	mainpane.setSize(size);
	mainpane.setOrigin(size.x / 2, size.y / 2);
	mainpane.setPosition(100, 100);

	logger::INFO("Pane" + std::to_string(pid) + " created");
}

Pane::~Pane()
{
	logger::INFO("Pane " + std::to_string(PID) + " destroyed.");
}

void Pane::setPosition(sf::Vector2f &newpos)
{
	mainpane.setPosition(newpos);
}