#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML\Graphics.hpp>

#include <vector>

class Renderer
{
public:
	Renderer(sf::RenderWindow *target_window);
	~Renderer();

	void addToQueue(sf::RectangleShape &object); //  |   > OVERLOAD
	void render();

private:
	sf::RenderWindow *window;
	std::vector<sf::RectangleShape> render_queue;
};

#endif
