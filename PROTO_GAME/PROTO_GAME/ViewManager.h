#pragma once

#include <memory>
#include <SFML/Graphics.hpp>


namespace sf
{
	class RenderWindow;
}

class ViewManager
{
private:
	const static int g_borderOffset;
	const static float g_viewMoveSpeed;

	sf::RenderWindow & m_window;

	sf::Vector2f m_viewInitialSize;
	sf::View m_view;
	sf::Vector2u m_resolution;
	sf::Vector2f m_fieldSize;

	float m_scaleFactor = 1.f;
	float m_maxScaleFactor;
	const float m_minScaleFactor = .5f;
	
public:
	ViewManager(sf::RenderWindow & window, const sf::Vector2f & fieldSize);

	ViewManager & operator=(const ViewManager & other) = delete;
	ViewManager(const ViewManager & other) = delete;

	void update(float dt);
	void mouseWheelScrolled(float delta);
};

