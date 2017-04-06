#include "Environment.hpp"
#include "logger.hpp"

#include <time.h>

namespace environment
{
	std::string getTimestamp()
	{
		time_t $time = time(0);

		int seconds = $time % 60;
		$time /= 60;

		int minutes = $time % 60;
		$time /= 60;

		int hours = $time % 24;
		$time /= 24;

		std::string seconds_s(std::to_string(seconds));
		std::string minutes_s(std::to_string(minutes));
		std::string hours_s(std::to_string(hours));

		if (seconds < 10)
			seconds_s.insert(0, "0");

		if (minutes < 10)
			minutes_s.insert(0, "0");

		if (hours < 10)
			hours_s.insert(0, "0");

		std::string timestamp = hours_s + ":" + minutes_s + ":" + seconds_s;

		return timestamp;
	}
}

//---------- CLASS ------------

Environment::Environment(sf::VideoMode dimensions, std::string title)
{
	window = new sf::RenderWindow;
	window->create(sf::VideoMode(dimensions), title, sf::Style::Close | sf::Style::Titlebar);

	logger::INFO("New environment created.");
}

Environment::~Environment()
{
	logger::INFO("Environment destroyed.");
}

void Environment::main()
{
	logger::INFO("Entering main loop.");

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return;
			}
		}

		window->clear(sf::Color::Blue);
		window->display();
	}
}
