#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics\RenderWindow.hpp>

class Taskbar;
class Pane;
class Renderer;

class Environment
{
public:
	Environment(sf::VideoMode dimensions, std::string title, int envid);
	~Environment();

	int environmentID;

	sf::RenderWindow *window;
	Taskbar *taskbar;
	Renderer *renderman;

	void main();
	void switchFocusedPaneTo(Pane* pane);

private:
	std::vector<Pane*> panes;
	Pane *nullPane;
	Pane *focusedPane = nullPane;
};

const std::string ENVIRONMENT_VERSION("0.0.642");

#endif /* ENVIRONMENT_HPP*/
