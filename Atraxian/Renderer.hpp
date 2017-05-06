#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML\Graphics.hpp>
#include <vector>

class Environment;

class Renderer
{
public:
	Renderer(Environment *target_env);
	~Renderer();

	void addToQueue(sf::Drawable *object);
	void removeFromQueue(sf::Drawable *object);
	void pushBack(sf::Drawable *object);
	void clearQueue();
	void render();

private:
	Environment *environment;
	std::vector<sf::Drawable*> render_queue;
};

#endif /* RENDERER_HPP */
