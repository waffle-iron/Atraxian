#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML\Graphics.hpp>

#include <vector>

class Renderer
{
public:
	Renderer(sf::RenderWindow *target_window);
	~Renderer();

	void addToQueue(sf::Drawable *object);
	void removeFromQueue(sf::Drawable *object);
	void pushBack(sf::Drawable *object);
	void clearQueue();
	void render();

private:
	sf::RenderWindow *window;
	std::vector<sf::Drawable*> render_queue;
};

#endif
