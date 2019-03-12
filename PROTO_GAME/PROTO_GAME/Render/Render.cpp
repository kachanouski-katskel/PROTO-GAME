#include "Render.h"
#include "DisplayObject.h"

#include <SFML/Graphics.hpp>

using namespace ProtoGame;
Render* Render::g_instance = nullptr;
sf::RenderWindow* Render::g_window = nullptr;

Render::Render() 
{

}

Render::~Render() 
{
}

void Render::update() 
{
	g_window->clear();

	for (auto displayObject : m_renderObjects)
	{
		if (!displayObject->isVivible())
		{
			continue;
		}

		g_window->draw(*displayObject->getSprite());
	}

	g_window->display();
}

void ProtoGame::Render::addChild(DisplayObject * object)
{
	m_renderObjects.push_back(std::make_shared<DisplayObject>(*object));
}

Render* Render::getInstance() 
{
	if (g_instance == nullptr) {
		g_instance = new Render();
	}
	return g_instance;
}

void Render::destroyInstance() 
{
	delete g_instance;
	g_instance = nullptr;
}

void ProtoGame::Render::initWindow(sf::RenderWindow * window)
{
	g_window = window;
}


