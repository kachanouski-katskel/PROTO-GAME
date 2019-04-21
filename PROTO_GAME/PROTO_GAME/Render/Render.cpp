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
		for (auto drawable : displayObject->getDrawables())
		{
			g_window->draw(*drawable);
		}		
	}

	/*sf::View view = g_window->getView();
	view.setRotation(view.getRotation() + 0.1f);
	g_window->setView(view);*/
	g_window->display();
}

void Render::addChild(DisplayObject * object)
{
	m_renderObjects.push_back(object);
}

void Render::removeChild(DisplayObject* object)
{
	m_renderObjects.erase(
		std::remove_if(m_renderObjects.begin(), m_renderObjects.end(), 
			[object](DisplayObject* renderObject) 
			{
				return object == renderObject;
			}
		),
		m_renderObjects.end()
	);
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


