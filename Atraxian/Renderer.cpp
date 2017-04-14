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
 	render_queue.push_back(&object);
}

void Renderer::removeFromQueue(sf::RectangleShape *object)
{
	for (size_t i = 0; i < render_queue.size(); i++)
	{
		if (object == render_queue[i])
		{
			render_queue.erase(std::remove(render_queue.begin(), render_queue.end(), object), render_queue.end());

			break;
		}
	}

//	logger::DEBUG("removed something from the render queue");
}

void Renderer::render()
{
	if (!render_queue.empty())
	{
		for (size_t i = 0; i < render_queue.size(); i++)
		{
			window->draw(*render_queue[i]);
		}
	}
}
