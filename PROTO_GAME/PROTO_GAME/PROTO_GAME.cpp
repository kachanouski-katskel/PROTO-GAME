#include <SFML/Graphics.hpp>
#include "Render/Render.h"
#include "Render/DisplayObject.h"
#include "Render/Vec2.h"
#include "Game/GameBase.h"
#include "Storage/TextureStorage.h"

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
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				m_game->MouseMoved(event.mouseMove.x, event.mouseMove.y);
			}
		}

		sf::Time dtime = clock.restart();
		float dt = dtime.asSeconds();

		if (m_game != nullptr)
		{
			m_game->Update(dt);
		}
		ProtoGame::Render::getInstance()->update();
	}

	ProtoGame::Render::destroyInstance();

	return 0;
}