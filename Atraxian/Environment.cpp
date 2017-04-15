#include "Environment.hpp"
#include "logger.hpp"
#include "Renderer.hpp"
#include "Taskbar.hpp"
#include "Pane.hpp"

#include <time.h>
#include <filesystem>

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
		focusedPane->defocus();

	pane->focus();
	focusedPane = pane;

	logger::INFO("Selected Pane" + std::to_string(focusedPane->PID));

	// TODO: allow panes to be focused by clicking any of their objects, even borders (perhaps a struct?)
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
					if (panes.size() > 0) // make sure there are panes
					{
						bool selected = false;

						for (size_t i = 0; i < panes.size(); i++) // all the panes
						{
							if (mouseIsOver(panes[i]->titlebar, *window)) // check if we're on the bar
							{
								if (mouseIsOver(panes[i]->closebutton, *window)) // then on the close button
								{
									int pid = panes[i]->PID; // get a temp PID

									rm.removeFromQueue(&panes[i]->mainpane);
									rm.removeFromQueue(&panes[i]->titlebar);
									rm.removeFromQueue(&panes[i]->closebutton);
									rm.removeFromQueue(&panes[i]->leftborder);
									rm.removeFromQueue(&panes[i]->rightborder);
									rm.removeFromQueue(&panes[i]->bottomborder);
									panes.erase(std::remove(panes.begin(), panes.end(), panes[i]), panes.end());

									logger::INFO("Removed Pane" + std::to_string(pid)); // use the temp PID

									break;
								}

								focusPane(panes[i]);

								selected = true;

								break;
							}
						}

						// if we clicked, but it wasn't in part of a pane, unfocus the focused pane.
						if (!selected && panes.size() > 0 && focusedPane->focused)
						{
							focusedPane->defocus();
						}
					}

					if (mouseIsOver(taskbar->bar, *window)) // if we click the taskbar
					{
						if (mouseIsOver(taskbar->start_button, *window)) // clicked the startbutton
						{
							logger::DEBUG("clicked the start button");

							taskbar->start_button.setFillColor(sf::Color::Green); 

							focusedPane->defocus(); // we defocus it because we are focused on the start menu while we do this, we will refocus when the start menu is closed.
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (mouseIsOver(taskbar->start_button, *window)) // let go of the start menu
				{
					logger::DEBUG("released the start button");

					taskbar->start_button.setFillColor(sf::Color::Red);

					focusedPane->focus(); // refocus the panel.
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::N) // NEW PANE HOTKEY
				{
					Pane* newpane = new Pane(sf::Vector2f(200, 300), panes.size() + 1, window);
					rm.addToQueue(newpane->titlebar);
					rm.addToQueue(newpane->mainpane);
					rm.addToQueue(newpane->closebutton);
					rm.addToQueue(newpane->leftborder);
					rm.addToQueue(newpane->rightborder);
					rm.addToQueue(newpane->bottomborder);
					panes.push_back(newpane);

					focusPane(newpane);
				}
				else if (panes.size() > 0 && event.key.code == sf::Keyboard::Delete) // DELETE PANE HOTKEY
				{
					int pid = focusedPane->PID;

					rm.removeFromQueue(&focusedPane->mainpane);
					rm.removeFromQueue(&focusedPane->titlebar);
					rm.removeFromQueue(&focusedPane->closebutton);
					rm.removeFromQueue(&focusedPane->leftborder);
					rm.removeFromQueue(&focusedPane->rightborder);
					rm.removeFromQueue(&focusedPane->bottomborder);
					panes.erase(std::remove(panes.begin(), panes.end(), focusedPane), panes.end());

					logger::INFO("Removed Pane" + std::to_string(pid));
				}
			}
		} // event loop

		{
			// if we are holding the left alt key and space at the same time, and there is at least one pane, center it.
			if (panes.size() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				focusedPane->setPosition(sf::Vector2f(window->getView().getCenter().x, window->getView().getCenter().y + window->getSize().y));
			}
			else if (panes.size() > 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseIsOver(focusedPane->titlebar, *window))
			// if we are left clicking, panes exist, and are holding over the focused one, then move it to the position of the mouse. used for click and drag positioning.
			{
				focusedPane->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
			}
		}

		window->clear(sf::Color::Blue);
		rm.render();
		window->display();
	}
}
