#include "Pane.hpp"
#include "logger.hpp"

Pane::Pane(const sf::Vector2f size, int pid, sf::RenderWindow *window_)
{
	window = window_;
	PID = pid;

	mainpane.setFillColor(sf::Color::White);
	mainpane.setSize(size);
	mainpane.setOrigin(size.x / 2, size.y / 2);
	mainpane.setPosition(window->getView().getCenter());

	titlebar.setFillColor(sf::Color::Black);
	titlebar.setSize(sf::Vector2f(mainpane.getLocalBounds().width, 32));
	titlebar.setOrigin(titlebar.getLocalBounds().width / 2, titlebar.getLocalBounds().height / 2);
	titlebar.setPosition(mainpane.getPosition().x, mainpane.getPosition().y - mainpane.getLocalBounds().height / 2 - (titlebar.getLocalBounds().height / 2));

	closebutton.setFillColor(sf::Color::Red);
	closebutton.setSize(sf::Vector2f(titlebar.getLocalBounds().height, titlebar.getLocalBounds().height));
	closebutton.setOrigin(closebutton.getLocalBounds().width / 2, closebutton.getLocalBounds().height / 2);
	closebutton.setPosition((titlebar.getPosition().x + titlebar.getLocalBounds().width / 2) - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y);


	const float BORDER_PADDING = mainpane.getLocalBounds().width / 32.0f;

	leftborder.setFillColor(sf::Color::Yellow);
	leftborder.setSize(sf::Vector2f(BORDER_PADDING, mainpane.getLocalBounds().height + titlebar.getLocalBounds().height));
	leftborder.setOrigin(leftborder.getLocalBounds().width / 2, leftborder.getLocalBounds().height / 2);
	leftborder.setPosition((mainpane.getPosition().x - mainpane.getLocalBounds().width / 2) - leftborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);

	rightborder.setFillColor(sf::Color::Yellow);
	rightborder.setSize(sf::Vector2f(BORDER_PADDING, mainpane.getLocalBounds().height + titlebar.getLocalBounds().height));
	rightborder.setOrigin(rightborder.getLocalBounds().width / 2, rightborder.getLocalBounds().height / 2);
	rightborder.setPosition((mainpane.getPosition().x + mainpane.getLocalBounds().width / 2 + (rightborder.getLocalBounds().width)) - rightborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);

	bottomborder.setFillColor(sf::Color::Yellow);
	bottomborder.setSize(sf::Vector2f(mainpane.getLocalBounds().width + (BORDER_PADDING * 2), BORDER_PADDING)); // TOOD: make the Y size of this a global thing, called BORDER_WIDTH that all borders use.
	bottomborder.setOrigin(bottomborder.getLocalBounds().width / 2, bottomborder.getLocalBounds().height / 2);
	bottomborder.setPosition(mainpane.getPosition().x, mainpane.getPosition().y + (mainpane.getLocalBounds().height / 2) + bottomborder.getLocalBounds().height / 2);

	boundingbox.setFillColor(sf::Color::Magenta);
	boundingbox.setSize(sf::Vector2f(mainpane.getLocalBounds().width + (rightborder.getLocalBounds().width + leftborder.getLocalBounds().width), mainpane.getLocalBounds().height + (titlebar.getLocalBounds().height + bottomborder.getLocalBounds().height)));
	boundingbox.setOrigin(boundingbox.getLocalBounds().width / 2, boundingbox.getLocalBounds().height / 2);
	
	boundingbox.setPosition(mainpane.getPosition().x, mainpane.getPosition().y - ((titlebar.getLocalBounds().height / 2) - (bottomborder.getLocalBounds().height / 2)));
//	boundingbox.setPosition(mainpane.getPosition().x + titlebar.getLocalBounds().height / 2, mainpane.getPosition().y);
//  adding a thing like that to the x makes it look like a shadow, might keep this for later.

	setPosition(window->getView().getCenter());

	logger::INFO("Pane" + std::to_string(pid) + " created");
}

Pane::~Pane()
{
	logger::INFO("Pane " + std::to_string(PID) + " destroyed.");
}

void Pane::setPosition(const sf::Vector2f newpos)
{
	titlebar.setPosition(newpos);
	mainpane.setPosition(titlebar.getPosition().x, titlebar.getPosition().y + mainpane.getLocalBounds().height / 2 + (titlebar.getLocalBounds().height / 2));
	closebutton.setPosition((titlebar.getPosition().x + titlebar.getLocalBounds().width / 2) - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y);
	leftborder.setPosition((mainpane.getPosition().x - mainpane.getLocalBounds().width / 2) - leftborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);
	rightborder.setPosition((mainpane.getPosition().x + mainpane.getLocalBounds().width / 2 + (rightborder.getLocalBounds().width)) - rightborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);
	bottomborder.setPosition(mainpane.getPosition().x, mainpane.getPosition().y + (mainpane.getLocalBounds().height / 2) + bottomborder.getLocalBounds().height / 2);
	boundingbox.setPosition(mainpane.getPosition().x, mainpane.getPosition().y - ((titlebar.getLocalBounds().height / 2) - (bottomborder.getLocalBounds().height / 2)));
}

void Pane::focus()
{
	focused = true;

	titlebar.setFillColor(sf::Color::Green);
	leftborder.setFillColor(sf::Color::Green);
	rightborder.setFillColor(sf::Color::Green);
	bottomborder.setFillColor(sf::Color::Green);
}

void Pane::defocus()
{
	focused = false;

	titlebar.setFillColor(sf::Color::Black);
	leftborder.setFillColor(sf::Color::Black);
	rightborder.setFillColor(sf::Color::Black);
	bottomborder.setFillColor(sf::Color::Black);
}
