#include <iostream>
#include <SFML/Graphics.hpp>



void RenderFullScreen(sf::RenderWindow* window)
{
	float x = (float) window->getSize().x;
	float y = (float) window->getSize().y;

	sf::Vertex vertices[4];
	vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	vertices[1].position = sf::Vector2f(x, 0.0f);
	vertices[2].position = sf::Vector2f(x, y);
	vertices[3].position = sf::Vector2f(0.0f, y);

	window->draw(vertices, 4, sf::Quads);
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	sf::Shader sh;
	if (sh.loadFromFile("data/shaders/shader.frag", sf::Shader::Fragment))
	{
		std::cout << "success" << std::endl;
	}
	else
	{
		std::cout << "fail" << std::endl;
	}

	sf::Clock clock;
	sf::Vector2f explosionPoint(400.0f, 300.0f);

	while (window.isOpen())
	{
		window.clear();
		sf::Shader::bind(&sh);
		sh.setParameter("explosionPoint", explosionPoint);
		sh.setParameter("currTime", clock.getElapsedTime().asSeconds());
		sh.setParameter("waveSpeed", 250.0f);
		RenderFullScreen(&window);
		window.display();

		sf::Event evt;
		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					clock.restart();
					explosionPoint = sf::Vector2f((float) evt.mouseButton.x, (float) evt.mouseButton.y);
					std::cout << explosionPoint.x << " " << explosionPoint.y << std::endl;
					break;
			}
		}
	}
	
	return 0;
}

