#include "Environment.hpp"
#include "logger.hpp"
#include "Renderer.hpp"
#include "Taskbar.hpp"

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

Environment::Environment(sf::VideoMode dimensions, sf::String title)
{
	logger::INFO("Creating new Environment instance...");

	window = new sf::RenderWindow;
	window->create(dimensions, title, sf::Style::Close | sf::Style::Titlebar);

	taskbar = new Taskbar(window);

	logger::INFO("New Environment instance created.");
}

Environment::~Environment()
{
	delete window;
	delete taskbar;

	logger::INFO("Environment destroyed.");
}

bool mouseIsOver(sf::Shape &object, sf::RenderWindow &window)
{
	if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		return true;
	else
		return false;
}

void Environment::main()
{
	Renderer rm(window);

	rm.addToQueue(taskbar->bar);
	rm.addToQueue(taskbar->start_button);
	rm.addToQueue(taskbar->div);

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
//					logger::DEBUG("left clicked at " + std::to_string(sf::Mouse::getPosition().x) + ", " + std::to_string(sf::Mouse::getPosition().y));

					if (mouseIsOver(taskbar->start_button, *window))
					{
						logger::DEBUG("clicked the start button");

						taskbar->start_button.setFillColor(sf::Color::Green);
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (mouseIsOver(taskbar->start_button, *window))
				{
					logger::DEBUG("released the start button");

					taskbar->start_button.setFillColor(sf::Color::Red);
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::N)
				{
					logger::DEBUG("windows not yet implemented");
				}
			}
		}

		window->clear(sf::Color::Blue);

		rm.render();

		window->display();
	}
}
