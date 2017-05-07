#include "Logger.hpp"
#include "Environment.hpp"
#include "Filesystem.hpp"
#include "Renderer.hpp"
#include "Taskbar.hpp"
#include "Pane.hpp"
#include "MapleParser.hpp"
#include "Util.hpp"

#include <ctime>

Environment::Environment(sf::VideoMode dimensions, std::string title, int envID)
{
	if (!environment::util::fs_ready())
		environment::util:: ready_fs();

	logger::setOutputDir("root", ("environment" + std::to_string(envID)));

	logger::INFO("Creating new Environment instance...");
	environmentID = envID;

	window = new sf::RenderWindow;
	window->create(dimensions, (title + " (" + std::to_string(envID) + ")"), (sf::Style::Close | sf::Style::Titlebar));
	window->setFramerateLimit(60);

	taskbar = new Taskbar(this);

	nullPane = new Pane(sf::Vector2f(0, 0), "null", 0, window);

	logger::INFO("New Environment instance created.");

	parser::getInfo("root//apps//test.maple");
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

void Environment::switchFocusedPaneTo(Pane* pane)
{
	if (panes.size() > 1 && pane != nullPane)
		focusedPane->defocus();

	focusedPane = pane;
	focusedPane->focus();
}

void Environment::main()
{
	Renderer rm(this->window);

	rm.addToQueue(&taskbar->bar);
	rm.addToQueue(&taskbar->start_button);
	rm.addToQueue(&taskbar->div);
//	rm.addToQueue(&taskbar->time);

	bool dragging_pane(false);
	
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				panes.clear();
				rm.clearQueue();
				window->close();
				return;
			}

			else if (event.type == sf::Event::EventType::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (!panes.empty()) // make sure there are panes
					{
						bool selected(false);
						bool already_selected(false);

						// if we clicked on any pane
						for (int i = panes.size() - 1; i >= 0; i--)
						{
							if (mouseIsOver(panes[i]->boundingbox, *window)) // check if we're in the pane
							{
								logger::INFO("Clicked inside the boundingbox of Pane" + std::to_string(panes[i]->PID));

								if (mouseIsOver(panes[i]->titlebar, *window)) // then on the title bar
								{
									logger::INFO("Clicked inside the titlebar of Pane" + std::to_string(panes[i]->PID));

									if (mouseIsOver(panes[i]->closebutton, *window)) // then the close button
									{
										logger::INFO("Clicked the close button of Pane" + std::to_string(panes[i]->PID));

										rm.removeFromQueue(&panes[i]->titletext);
										rm.removeFromQueue(&panes[i]->titlebar);
										rm.removeFromQueue(&panes[i]->mainpane);
										rm.removeFromQueue(&panes[i]->closebutton);
										rm.removeFromQueue(&panes[i]->leftborder);
										rm.removeFromQueue(&panes[i]->rightborder);
										rm.removeFromQueue(&panes[i]->bottomborder);

										delete panes[i];
										panes.erase(std::remove(panes.begin(), panes.end(), panes[i]), panes.end());
										break;
									}
									else
									{
										logger::INFO("Clicked only the titlebar, started dragging.");

										dragging_pane = true;
									}
								}

								if (panes[i] == focusedPane)
								{
									already_selected = true;

									logger::INFO("Pane" + std::to_string(focusedPane->PID) + " was already focused.");
								}
								else // wasn't already selected.
								{
									logger::INFO("Pane" + std::to_string(focusedPane->PID) + " was not already focused.");

									switchFocusedPaneTo(panes[i]);
									selected = true;

									logger::INFO("Bringing Pane" + std::to_string(focusedPane->PID) + " to the top of the Render Queue.");
									rm.pushBack(&focusedPane->titletext);
									rm.pushBack(&focusedPane->titlebar);
									rm.pushBack(&focusedPane->closebutton);
									rm.pushBack(&focusedPane->mainpane);
									rm.pushBack(&focusedPane->leftborder);
									rm.pushBack(&focusedPane->rightborder);
									rm.pushBack(&focusedPane->bottomborder);
									rm.pushBack(&focusedPane->titletext);
								}

								break;
							}
						}

						// if we didn't select anything, do nothing.
						// if there is nothing we *could have* selected, do nothing (because they might have clicked the close button).
						if (!already_selected && !panes.empty())
						{
							if (!selected)
							{
								if (focusedPane != nullPane)
								{
									logger::INFO("Nothing was selected. (Not even Pane0 D:)");

									focusedPane->defocus();
									focusedPane = nullPane;
								}
								else
								{
									logger::INFO("No pane was already selected.");
								}
							}
							else
							{
								logger::INFO("Something new was selected. (Pane" + std::to_string(focusedPane->PID) + ")");
							}
						}
					}

					if (mouseIsOver(taskbar->bar, *window)) // if we click the taskbar
					{
						if (mouseIsOver(taskbar->start_button, *window)) // clicked the startbutton
						{
							logger::INFO("Clicked the start button.");

							taskbar->start_button.setFillColor(sf::Color::Green);

							if (!panes.empty())																				// TODO: this
								focusedPane->defocus(); // we defocus it because we are focused on the start menu while we do this, we will refocus when the start menu is closed.
						}
					}
				}
			}

			else if (event.type == sf::Event::EventType::MouseButtonReleased)
			{
				if (mouseIsOver(taskbar->bar, *window))
				{
					if (mouseIsOver(taskbar->start_button, *window)) // let go of the start menu
					{
						logger::INFO("Released the start button.");

						taskbar->start_button.setFillColor(sf::Color::Red);

//						if (!panes.empty() && focusedPane->focused == true)
//							focusedPane->focus(); // refocus the panel.

//						we want to refocus the pane only if it was already focused.						
					}
				}

				if (dragging_pane)
				{
					logger::INFO("Stopped dragging Pane" + std::to_string(focusedPane->PID) + ".");

					dragging_pane = false;
				}
			}

			else if (event.type == sf::Event::EventType::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::N) // NEW PANE HOTKEY
				{
					const int PID = panes.size() + 1;
					Pane* newpane = new Pane(sf::Vector2f(200, 300), "Pane" + std::to_string(PID), PID, window);

//					rm.addToQueue(&newpane->boundingbox);
					rm.addToQueue(&newpane->titletext);
					rm.addToQueue(&newpane->titlebar);
					rm.addToQueue(&newpane->closebutton);
					rm.addToQueue(&newpane->mainpane);
					rm.addToQueue(&newpane->leftborder);
					rm.addToQueue(&newpane->rightborder);
					rm.addToQueue(&newpane->bottomborder);
					rm.addToQueue(&newpane->titletext);
					panes.push_back(newpane); // add it to the stack

					switchFocusedPaneTo(newpane);
				}
				else if (focusedPane != nullPane && event.key.code == sf::Keyboard::Key::Delete) // DELETE PANE HOTKEY
				{
					rm.removeFromQueue(&focusedPane->titletext);
					rm.removeFromQueue(&focusedPane->titlebar);
					rm.removeFromQueue(&focusedPane->mainpane);
					rm.removeFromQueue(&focusedPane->closebutton);
					rm.removeFromQueue(&focusedPane->leftborder);
					rm.removeFromQueue(&focusedPane->rightborder);
					rm.removeFromQueue(&focusedPane->bottomborder);

					delete focusedPane;
					panes.erase(std::remove(panes.begin(), panes.end(), focusedPane), panes.end()); // remove it from the stack
					focusedPane = nullPane;
				}
			}
		} // event loop

		{
			// if we are holding the left alt key and space at the same time, and there is at least one pane, center it.
			if (!panes.empty() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				focusedPane->setPosition(sf::Vector2f(window->getView().getCenter()));

				logger::INFO("Pane" + std::to_string(focusedPane->PID) + " centered.");
			}
			// if we are left clicking, panes exist, and are holding over the focused one, then move it to the position of the mouse. used for click and drag positioning.
			else if (dragging_pane)
			{
				sf::Vector2i move_origin;
				move_origin.x = sf::Mouse::getPosition(*window).x;
				move_origin.y = sf::Mouse::getPosition(*window).y;

				focusedPane->setPosition(sf::Vector2f(move_origin));
			}
		}

//		taskbar->time.setString(environment::getTimestamp());
//		taskbar->time.setOrigin(sf::Vector2f(taskbar->time.getLocalBounds().width / 2, taskbar->time.getLocalBounds().height / 2));
//		taskbar->time.setPosition(sf::Vector2f((taskbar->bar.getPosition().x * 2) - (taskbar->time.getLocalBounds().width / 1.7), taskbar->bar.getPosition().y - (taskbar->time.getLocalBounds().height / 2.5)));

		window->clear(sf::Color::Blue);
		rm.render();
		window->display();
	}
}
