#include "Environment.hpp"
#include "logger.hpp"
#include "Renderer.hpp"
#include "Taskbar.hpp"
#include "Pane.hpp"

#include <ctime>
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

	nullPane = new Pane(sf::Vector2f(0, 0), 0, window);

	logger::INFO("New Environment instance created.");
}

Environment::~Environment()
{
	logger::INFO("Cleaning up...");

	delete window;
	delete taskbar;
	delete focusedPane;

	logger::INFO("Environment destroyed.");
}

bool mouseIsOver(sf::Shape &object, sf::RenderWindow &window)
{
	if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		return true;
	else
		return false;
}

void Environment::focusPane(Pane* pane)
{
	if (panes.size() > 1 && pane != nullPane)
	{
		focusedPane->active = false;
		focusedPane->defocus();
	}

	focusedPane = pane;
	focusedPane->focus();
	focusedPane->active = true;
}

void Environment::main()
{
	Renderer rm(window);

	rm.addToQueue(&taskbar->bar);
	rm.addToQueue(&taskbar->start_button);
	rm.addToQueue(&taskbar->div);

	bool dragging_pane(false);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				panes.clear();
				rm.clearQueue();
				window->close();
				return;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (panes.size() > 0) // make sure there are panes
					{
						bool selected(false);
						bool already_selected(false);

						for (size_t i = 0; i < panes.size(); i++) // all the panes
						{
							if (mouseIsOver(panes[i]->boundingbox, *window)) // check if we're in the pane
							{
								logger::INFO("Clicked inside the boundingbox.");

								if (mouseIsOver(panes[i]->titlebar, *window)) // then on the title bar
								{
									logger::INFO("Clicked inside the titlebar.");

									if (mouseIsOver(panes[i]->closebutton, *window)) // then the close button
									{
										logger::INFO("Clicked the close button.");

										int temp_PID = panes[i]->PID;

										rm.removeFromQueue(&panes[i]->mainpane);
										rm.removeFromQueue(&panes[i]->titlebar);
										rm.removeFromQueue(&panes[i]->closebutton);
										rm.removeFromQueue(&panes[i]->leftborder);
										rm.removeFromQueue(&panes[i]->rightborder);
										rm.removeFromQueue(&panes[i]->bottomborder);
										panes.erase(std::remove(panes.begin(), panes.end(), panes[i]), panes.end());

										logger::INFO("Removed Pane" + std::to_string(temp_PID) + ".");

										break;
									}
									else // just on the titlebar
									{
										logger::INFO("Clicked only the titlebar, started dragging.");

										dragging_pane = true;
									}
								}

								if (panes[i] == focusedPane)
								{
									already_selected = true;

									logger::INFO("Pane was already focused.");
								}
								else // wasn't already selected.
								{
									logger::INFO("Pane was not already focused.");

									focusPane(panes[i]);
									selected = true;
								}

								break;
							}
						}

						if (!already_selected && panes.size() > 0)
						{
							if (!selected)
							{
								if (focusedPane != nullPane)
								{
									logger::INFO("Nothing was selected.");

									focusedPane->defocus();
									focusedPane->active = false;
									focusedPane = nullPane;
								}
							}
							else
							{
								logger::INFO("Something new was selected.");
							}
						}
					}

					if (mouseIsOver(taskbar->bar, *window)) // if we click the taskbar
					{
						if (mouseIsOver(taskbar->start_button, *window)) // clicked the startbutton
						{
							logger::INFO("Clicked the start button.");

							taskbar->start_button.setFillColor(sf::Color::Green);

							if (panes.size() > 0)
								focusedPane->defocus(); // we defocus it because we are focused on the start menu while we do this, we will refocus when the start menu is closed.
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (mouseIsOver(taskbar->bar, *window))
				{
					if (mouseIsOver(taskbar->start_button, *window)) // let go of the start menu
					{
						logger::INFO("Released the start button.");

						taskbar->start_button.setFillColor(sf::Color::Red);

//						if (panes.size() > 0 && focusedPane->focused == true)
//						{
//							focusedPane->focus(); // refocus the panel.
//						}

//						we want to refocus the pane only if it was already focused.						
					}
				}

				if (dragging_pane)
				{
					logger::INFO("Stopped dragging Pane" + std::to_string(focusedPane->PID) + ".");

					dragging_pane = false;
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::N) // NEW PANE HOTKEY
				{
					Pane* newpane = new Pane(sf::Vector2f(200, 300), panes.size() + 1, window);

//					rm.addToQueue(&newpane->boundingbox);

					rm.addToQueue(&newpane->titlebar);
					rm.addToQueue(&newpane->mainpane);
					rm.addToQueue(&newpane->closebutton);
					rm.addToQueue(&newpane->leftborder);
					rm.addToQueue(&newpane->rightborder);
					rm.addToQueue(&newpane->bottomborder);
					panes.push_back(newpane); // add it to the stack

					focusPane(newpane);
				}
				else if (panes.size() > 0 && event.key.code == sf::Keyboard::Delete) // DELETE PANE HOTKEY
				{
					int temp_PID = focusedPane->PID;

					rm.removeFromQueue(&focusedPane->mainpane);
					rm.removeFromQueue(&focusedPane->titlebar);
					rm.removeFromQueue(&focusedPane->closebutton);
					rm.removeFromQueue(&focusedPane->leftborder);
					rm.removeFromQueue(&focusedPane->rightborder);
					rm.removeFromQueue(&focusedPane->bottomborder);
					panes.erase(std::remove(panes.begin(), panes.end(), focusedPane), panes.end()); // remove it from the stack

					logger::INFO("Removed Pane" + std::to_string(temp_PID) + ".");
				}
			}
		} // event loop

		{
			// if we are holding the left alt key and space at the same time, and there is at least one pane, center it.
			if (panes.size() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				focusedPane->setPosition(sf::Vector2f(window->getView().getCenter()));

				logger::INFO("Centered Pane" + std::to_string(focusedPane->PID) + ".");
			}
			// if we are left clicking, panes exist, and are holding over the focused one, then move it to the position of the mouse. used for click and drag positioning.
			else if (dragging_pane)
			{
//				sf::Vector2f move_origin;
//				move_origin.x = sf::Mouse::getPosition(*window).x;
//				move_origin.y = sf::Mouse::getPosition(*window).y;

				focusedPane->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
			}
		}

		window->clear(sf::Color::Blue);
		rm.render();
		window->display();
	}
}
