#include "Renderer.hpp"
#include "logger.hpp"

Renderer::Renderer(sf::RenderWindow *target_window)
{
	logger::INFO("New Renderer instance created.");

	window = target_window;
}

Renderer::~Renderer()
{
	logger::INFO("Renderer isntance destroyed.");
}

void Renderer::addToQueue(sf::RectangleShape &object)
{
 	render_queue.push_back(object);
}

void Renderer::render()
{
	if (!render_queue.empty())
	{
		for (size_t i = 0; i < render_queue.size(); i++)
		{
			window->draw(render_queue[i]);
		}
	}
}
