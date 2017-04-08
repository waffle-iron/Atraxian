#include "Environment.hpp"
#include "logger.hpp"
#include "Renderer.hpp"

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

//---------- CLASS ----------

Environment::Environment(sf::VideoMode dimensions, std::string title)
{
	window = new sf::RenderWindow;
	window->create(sf::VideoMode(dimensions), title, sf::Style::Close | sf::Style::Titlebar);

	taskbar.setFillColor(sf::Color::White); // TODO: USERF:CUSTOMISE
	taskbar.setSize(sf::Vector2f(window->getSize().x, 40)); // as long as the window, and 35 pixels high
	taskbar.setOrigin(taskbar.getSize().x / 2, taskbar.getSize().y / 2); // center it
	taskbar.setPosition(window->getSize().x / 2, (window->getSize().y - (taskbar.getLocalBounds().height / 2)));
	// TODO: make the above two lines not generate warnings

	start_button.setFillColor(sf::Color::Green);
	start_button.setSize(sf::Vector2f(40, 40));
	start_button.setOrigin(start_button.getLocalBounds().width / 2, start_button.getLocalBounds().height / 2);
	start_button.setPosition(taskbar.getLocalBounds().left + 20, taskbar.getPosition().y);

	logger::INFO("New environment created.");
}

Environment::~Environment()
{
	delete window;

	logger::INFO("Environment destroyed.");
}

void Environment::main()
{
	Renderer rm(window);

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

		rm.addToQueue(taskbar);
		rm.addToQueue(start_button);
		rm.render();

		window->display();
	}
}
