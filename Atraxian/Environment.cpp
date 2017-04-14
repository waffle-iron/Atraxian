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

void Environment::main()
{
	Renderer rm(window);

	rm.addToQueue(taskbar->bar);
	rm.addToQueue(taskbar->start_button);
	rm.addToQueue(taskbar->div);

	desktop_background.setFillColor(sf::Color::Blue);
	desktop_background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

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
//					logger::DEBUG("left clicked at " + std::to_string(sf::Mouse::getPosition(*window).x) + ", " + std::to_string(sf::Mouse::getPosition(*window).y));

					for (size_t i = 0; i < panes.size(); i++)
					{
						if (mouseIsOver(panes[i]->mainpane, *window))
						{
							selectedPane = panes[i];
							logger::INFO("Selected Pane" + std::to_string(selectedPane->PID));

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

						logger::INFO("moving Pane" + std::to_string(selectedPane->PID) + " to " + std::to_string(sf::Mouse::getPosition(*window).x) + ", " + std::to_string(sf::Mouse::getPosition(*window).y));
						selectedPane->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
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
					Pane* newpane = new Pane(sf::Vector2f(100, 100), panes.size() + 1);
					rm.addToQueue(newpane->mainpane);
					panes.push_back(newpane);
					selectedPane = panes.back();
				}
				else if (event.key.code == sf::Keyboard::Delete) // DELETE PANE
				{
					int pid = selectedPane->PID;

					for (size_t i = 0; i < panes.size(); i++)
					{
						if (selectedPane == panes[i])
						{
							rm.removeFromQueue(&selectedPane->mainpane);
							panes.erase(std::remove(panes.begin(), panes.end(), selectedPane), panes.end());
						}
					}

					logger::INFO("Removed Pane" + std::to_string(pid));
				}
			}
		}

		window->clear(sf::Color::Blue);

//		window->draw(desktop_background);
		rm.render();

		window->display();
	}
}
