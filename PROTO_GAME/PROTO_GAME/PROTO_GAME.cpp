#include <SFML/Graphics.hpp>
#include "Render/Render.h"
#include "Render/DisplayObject.h"
#include "Render/Vec2.h"
#include "Game/GameBase.h"
#include "Storage/TextureStorage.h"

#include <ctime>
#include <iostream>
ProtoGame::GameBase* m_game = nullptr;


int main()
{
	sf::Vector2f resolution;
	resolution.x = 1200; // sf::VideoMode::getDesktopMode().width / 2;
	resolution.y = 960; // sf::VideoMode::getDesktopMode().height / 2;

	sf::RenderWindow window;
	window.create(
		sf::VideoMode(resolution.x, resolution.y),
		"Proto game");

	ProtoGame::Render::initWindow(&window);

	m_game = new ProtoGame::GameBase();
	m_game->Init();
	sf::Vector2f fieldSize{ m_game->getFieldSize().mPosX, m_game->getFieldSize().mPosY };

	const sf::Vector2f viewSize{ 400.f, 320.f };
	sf::View view(sf::Vector2f(viewSize.x / 2, viewSize.y / 2), viewSize);
	window.setView(view);

	const int borderOffset = 50;
	const float viewMoveSpeed = 100;

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
		}

		sf::Time dtime = clock.restart();
		float dt = dtime.asSeconds();

		// TODO: Move to ViewManager
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			//std::cout << "local position: X - " << localPosition.x << ", Y - " << localPosition.y << std::endl;
			/*
			check if mouse position is within area close to border (borderOffset)
			if can move to appropriate side
				move with some fixed speed
			*/
			float deltaMove = dt * viewMoveSpeed;
			if (localPosition.x < borderOffset && localPosition.x >= 0)
			{
				view.move(-deltaMove, 0);
			}
			if (localPosition.y < borderOffset && localPosition.y >= 0)
			{
				view.move(0, -deltaMove);
			}
			if (localPosition.x > resolution.x - borderOffset && localPosition.x <= resolution.x)
			{
				view.move(deltaMove, 0);
			}
			if (localPosition.y > resolution.y - borderOffset && localPosition.y <= resolution.y)
			{
				view.move(0, deltaMove);
			}

			/*
			if view position is out of field
				normalize position
			*/
			sf::Vector2f viewPosition = view.getCenter();

			viewPosition.x = std::max(viewSize.x / 2, std::min(fieldSize.x - viewSize.x / 2, viewPosition.x));
			viewPosition.y = std::max(viewSize.y / 2, std::min(fieldSize.y - viewSize.y / 2, viewPosition.y));

			view.setCenter(viewPosition);
			window.setView(view);
		}

		//std::cout << 1.0 / dt << std::endl;
		if (m_game != nullptr)
		{
			clock_t c = std::clock();
			m_game->Update(dt);
			//std::cout << "Game update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl;
		}
		clock_t c = std::clock();
		ProtoGame::Render::getInstance()->update();
		//std::cout << "Render update: " << double(std::clock() - c) / CLOCKS_PER_SEC << "s" << std::endl << std::endl;
	}

	ProtoGame::Render::destroyInstance();

	return 0;
}