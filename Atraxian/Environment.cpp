#include "Environment.hpp"
#include "logger.hpp"
#include "Renderer.hpp"
#include "Taskbar.hpp"
#include "Pane.hpp"

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
	window->setFramerateLimit(60);

	taskbar = new Taskbar(window);

	logger::INFO("New Environment instance created.");
}

Environment::~Environment()
{
	delete window;
	delete taskbar;

	logger::INFO("Environment destroyed.");
}

bool mouseIsOver(sf::RectangleShape &object, sf::RenderWindow &window)
{
	if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		return true;
	else
		return false;
}

void Environment::focusPane(Pane* pane)
{
	if (panes.size() > 1)
		focusedPane->mainpane.setFillColor(sf::Color::White);

	focusedPane = pane;

	focusedPane->mainpane.setFillColor(sf::Color::Magenta);

	logger::INFO("Selected Pane" + std::to_string(focusedPane->PID)); 
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
					for (size_t i = 0; i < panes.size(); i++)
					{
						if (mouseIsOver(panes[i]->mainpane, *window))
						{
							focusPane(panes[i]);

							break;
						}
					}

					if (mouseIsOver(taskbar->bar, *window))
					{
						if (mouseIsOver(taskbar->start_button, *window))
						{
							logger::DEBUG("clicked the start button");

							taskbar->start_button.setFillColor(sf::Color::Green);
						}
					}
					else if (panes.size() > 0)
					{
						logger::INFO("moving Pane" + std::to_string(focusedPane->PID) + " to " + std::to_string(sf::Mouse::getPosition(*window).x) + ", " + std::to_string(sf::Mouse::getPosition(*window).y));
						focusedPane->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
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
				if (event.key.code == sf::Keyboard::N) // NEW  PANE
				{
					Pane* newpane = new Pane(sf::Vector2f(100, 150), panes.size() + 1);
					rm.addToQueue(newpane->mainpane);
					panes.push_back(newpane);

					focusPane(newpane);
				}
				else if (event.key.code == sf::Keyboard::Delete) // DELETE PANE
				{
					int pid = focusedPane->PID;

					for (size_t i = 0; i < panes.size(); i++)
					{
						if (focusedPane == panes[i])
						{
							rm.removeFromQueue(&focusedPane->mainpane);
							panes.erase(std::remove(panes.begin(), panes.end(), focusedPane), panes.end());
						}
					}

					logger::INFO("Removed Pane" + std::to_string(pid));
				}
			}
		}

		window->clear(sf::Color::Blue);
		rm.render();
		window->display();
	}
}
