#include <SFML/Graphics.hpp>
#include "Render/Render.h"
#include "Render/DisplayObject.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	ProtoGame::Render::initWindow(&window);

	sf::Texture texture;
	texture.loadFromFile("resources/AnotherMan.png");
	ProtoGame::DisplayObject* obj = new ProtoGame::DisplayObject(&texture);
	obj->setVisible(true);
	ProtoGame::Render::getInstance()->addChild(obj);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ProtoGame::Render::getInstance()->update();
	}

	ProtoGame::Render::destroyInstance();

	return 0;
}