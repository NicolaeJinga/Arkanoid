#include<iostream>
#include "SFML/Graphics.hpp"
#include "Game.h"

int main()
{
	Game game;
	game.Init();
	sf::Clock clock;
	float dt = 0.0f;
	while(game.m_window.isOpen())
	{
		sf::Event event;
		while(game.m_window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				game.m_window.close();
		}
		dt = clock.restart().asSeconds();
		game.Update(dt);
		game.Draw();
		game.m_window.display();
	}
	return 0;
}