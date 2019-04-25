#include <SFML/Graphics.hpp>
#include "Render/Render.h"
#include "Render/DisplayObject.h"
#include "Render/Vec2.h"
#include "Game/GameBase.h"
#include "Storage/TextureStorage.h"

#include <ctime>
#include <iostream>
ProtoGame::GameBase* m_game = nullptr;

void mainLoop()
{

}

int main()
{
	sf::Vector2f resolution;
	resolution.x = 800; // sf::VideoMode::getDesktopMode().width / 2;
	resolution.y = 640; // sf::VideoMode::getDesktopMode().height / 2;

	sf::RenderWindow window;
	window.create(
		sf::VideoMode(resolution.x, resolution.y),
		"Proto game");

	ProtoGame::Render::initWindow(&window);

	m_game = new ProtoGame::GameBase();
	m_game->Init();

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		if (m_game != nullptr && m_game->isFinished())
		{
			window.close();
			continue;
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f trueCoords = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				m_game->MouseMoved(trueCoords.x, trueCoords.y);
			}
		}

		sf::Time dtime = clock.restart();
		float dt = dtime.asSeconds();
		//std::cout << 1.0 / dt << std::endl;
		if (m_game != nullptr)
		{
			clock_t c = std::clock();
			m_game->Update(dt);
			std::cout << "Game update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl;
		}
		clock_t c = std::clock();
		ProtoGame::Render::getInstance()->update();
		std::cout << "Render update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl << std::endl;
	}

	ProtoGame::Render::destroyInstance();

	return 0;
}