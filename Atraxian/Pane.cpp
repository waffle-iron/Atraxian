#include "Environment.hpp"
#include "Pane.hpp"
#include "logger.hpp"

Pane::Pane(const sf::Vector2f size, const std::string title, const int pid, sf::RenderWindow *window_)
{
	window = window_;
	PID = pid;

	mainpane.setFillColor(sf::Color::White);
	mainpane.setSize(size);
	mainpane.setOrigin(size.x / 2, size.y / 2);
	mainpane.setPosition(window->getView().getCenter());

	titlebar.setSize(sf::Vector2f(mainpane.getLocalBounds().width, 32));
	titlebar.setOrigin(titlebar.getLocalBounds().width / 2, titlebar.getLocalBounds().height / 2);
	titlebar.setPosition(mainpane.getPosition().x, mainpane.getPosition().y - mainpane.getLocalBounds().height / 2 - (titlebar.getLocalBounds().height / 2));

	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	titletext.setFont(font);
	titletext.setString(title);
	titletext.setCharacterSize(titlebar.getLocalBounds().height - 6);
	titletext.setOrigin(titletext.getLocalBounds().width / 2, titletext.getLocalBounds().height / 2);
	titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) - 8);

	closebutton.setFillColor(sf::Color::Red);
	closebutton.setSize(sf::Vector2f(titlebar.getLocalBounds().height, titlebar.getLocalBounds().height));
	closebutton.setOrigin(closebutton.getLocalBounds().width / 2, closebutton.getLocalBounds().height / 2);
	closebutton.setPosition((titlebar.getPosition().x + titlebar.getLocalBounds().width / 2) - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y);


	const float BORDER_PADDING = mainpane.getLocalBounds().width / 32.0f;

	leftborder.setSize(sf::Vector2f(BORDER_PADDING, mainpane.getLocalBounds().height + titlebar.getLocalBounds().height));
	leftborder.setOrigin(leftborder.getLocalBounds().width / 2, leftborder.getLocalBounds().height / 2);
	leftborder.setPosition((mainpane.getPosition().x - mainpane.getLocalBounds().width / 2) - leftborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);

	rightborder.setSize(sf::Vector2f(BORDER_PADDING, mainpane.getLocalBounds().height + titlebar.getLocalBounds().height));
	rightborder.setOrigin(rightborder.getLocalBounds().width / 2, rightborder.getLocalBounds().height / 2);
	rightborder.setPosition((mainpane.getPosition().x + mainpane.getLocalBounds().width / 2 + (rightborder.getLocalBounds().width)) - rightborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);

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

const sf::Vector3i focusedColour(109, 109, 109);
const sf::Vector3i defocusedColour(190, 190, 190);

void Pane::setPosition(const sf::Vector2f newpos)
{
	titlebar.setPosition(newpos);
	titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 2);
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

	titlebar.setFillColor(sf::Color(focusedColour.x, focusedColour.y, focusedColour.z));
	leftborder.setFillColor(sf::Color(focusedColour.x, focusedColour.y, focusedColour.z));
	rightborder.setFillColor(sf::Color(focusedColour.x, focusedColour.y, focusedColour.z));
	bottomborder.setFillColor(sf::Color(focusedColour.x, focusedColour.y, focusedColour.z));

	logger::INFO("Focused Pane" + std::to_string(PID) + ".");
}

void Pane::defocus()
{
	focused = false;

	titlebar.setFillColor(sf::Color(defocusedColour.x, defocusedColour.y, defocusedColour.z));
	leftborder.setFillColor(sf::Color(defocusedColour.x, defocusedColour.y, defocusedColour.z));
	rightborder.setFillColor(sf::Color(defocusedColour.x, defocusedColour.y, defocusedColour.z));
	bottomborder.setFillColor(sf::Color(defocusedColour.x, defocusedColour.y, defocusedColour.z));
	
	logger::INFO("Defocused Pane" + std::to_string(PID) + ".");
}
