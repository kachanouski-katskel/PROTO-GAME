#include <SFML/Graphics.hpp>
#include "Render/Render.h"
#include "Render/DisplayObject.h"
#include "Render/Vec2.h"
#include "Game/GameBase.h"
#include "Storage/TextureStorage.h"
#include "ViewManager.h"

#include <ctime>
#include <iostream>
ProtoGame::GameBase* m_game = nullptr;


int main()
{
	sf::Vector2f resolution;
	resolution.x = 1200;
	resolution.y = 960; 

	sf::RenderWindow window;
	window.create(
		sf::VideoMode(resolution.x, resolution.y),
		"Proto game");

	ProtoGame::Render::initWindow(&window);

	m_game = new ProtoGame::GameBase();
	m_game->Init();
	sf::Vector2f fieldSize{ m_game->getFieldSize().mPosX, m_game->getFieldSize().mPosY };

	ViewManager viewManager(window, fieldSize);

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
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2f trueCoords = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				m_game->MouseUp(trueCoords.x, trueCoords.y);
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					viewManager.mouseWheelScrolled(event.mouseWheelScroll.delta);
				}
			}
		}

		sf::Time dtime = clock.restart();
		float dt = dtime.asSeconds();

		clock_t c = std::clock();
		viewManager.update(dt);
		std::cout << "ViewManager update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl;

		//std::cout << 1.0 / dt << std::endl;
		if (m_game != nullptr)
		{
			clock_t c = std::clock();
			m_game->Update(dt);
			std::cout << "Game update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl;
		}
		c = std::clock();
		ProtoGame::Render::getInstance()->update();
		std::cout << "Render update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl << std::endl;
	}

	ProtoGame::Render::destroyInstance();

	return 0;
}