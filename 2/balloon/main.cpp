#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "particle_system.h"

int main()
{
	my::Vector2f minPoint(100.0f, 100.0f);
	my::Vector2f maxPoint(700.0f, 500.0f);
	sf::RenderWindow window(sf::VideoMode(800, 600), "window");
	ParticleSystem sys(minPoint, maxPoint);
	
	my::Vector2f center = (minPoint + maxPoint) * 0.5f;
	const float circleRadius = (maxPoint - minPoint).getLength() * 0.1f;
	const float pi = 3.141593f;
	const int count = 50;
	float ang = 0.0f;
	std::vector <Particle*> tmpParticles;

	for (int i = 0; i < count; i++)
	{
		ang = 2 * pi / float(count) * float(i);
		my::Vector2f pos = my::Vector2f(cos(ang), sin(ang)) * circleRadius + center;
		tmpParticles.push_back(sys.AddParticle(pos, 5.0f));
	}
	sys.AddVolumeLink(tmpParticles.data(), tmpParticles.size());

	for (int i = 0; i < count; i++)
	{
		sys.AddLink(sys.GetParticle(i), sys.GetParticle((i + 1) % count), 1.0f);
	}


	sf::Texture tex;
	tex.loadFromFile("data/Atlas.png");
	tex.setSmooth(true);
	
	while (window.isOpen())
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
					window.close();
			}
		}

		window.clear();
		
		for (int i = 0; i < sys.GetParticleCount(); i++)
		{
			sf::Vertex vertices[4];
			my::Vector2f pos = sys.GetParticle(i)->pos;
			float r = sys.GetParticle(i)->radius;
			vertices[0].position = sf::Vector2f(pos.x - r, pos.y - r);
			vertices[1].position = sf::Vector2f(pos.x + r, pos.y - r);
			vertices[2].position = sf::Vector2f(pos.x + r, pos.y + r);
			vertices[3].position = sf::Vector2f(pos.x - r, pos.y + r);

			for (int i = 0; i < 4; i++)
			{
				vertices[i].color = sf::Color::White;
			}

			float xSize = (float) tex.getSize().x;
			float ySize = (float) tex.getSize().y;
			vertices[0].texCoords = sf::Vector2f(xSize * 0.75f, ySize * 0.5f);
			vertices[1].texCoords = sf::Vector2f(xSize, ySize * 0.5f);
			vertices[2].texCoords = sf::Vector2f(xSize, ySize * 0.75f);
			vertices[3].texCoords = sf::Vector2f(xSize * 0.75f, ySize * 0.75f);

			window.draw(vertices, 4, sf::Quads, &tex);
		}
	
		window.display();
		sys.Update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sys.Push (my::Vector2f (0.0f, -0.002f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sys.Push(my::Vector2f(0.0f, 0.002f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sys.Push(my::Vector2f(-0.002f, 0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sys.Push(my::Vector2f(0.002f, 0.0f));
		}
	}
	
	return 0;
}
