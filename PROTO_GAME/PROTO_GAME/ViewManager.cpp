#include "ViewManager.h"


const int ViewManager::g_borderOffset = 50;
const float ViewManager::g_viewMoveSpeed = 100.f;

ViewManager::ViewManager(sf::RenderWindow & window, const sf::Vector2f & fieldSize)
	: m_window(window), m_fieldSize(fieldSize)
{
	m_resolution = m_window.getSize();
	m_viewInitialSize = { m_resolution.x / 3.f, m_resolution.y / 3.f };

	m_maxScaleFactor = std::min(m_fieldSize.x / m_viewInitialSize.x, m_fieldSize.y / m_viewInitialSize.y);

	m_view = sf::View(sf::Vector2f(m_viewInitialSize.x / 2, m_viewInitialSize.y / 2), m_viewInitialSize);
	m_window.setView(m_view);
}

void ViewManager::update(float dt)
{
	{
		sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
		//std::cout << "local position: X - " << localPosition.x << ", Y - " << localPosition.y << std::endl;
		/*
		check if mouse position is within area close to border (borderOffset)
		if can move to appropriate side
			move with some fixed speed
		*/
		float deltaMove = dt * g_viewMoveSpeed;
		if (localPosition.x < g_borderOffset && localPosition.x >= 0)
		{
			m_view.move(-deltaMove, 0);
		}
		if (localPosition.y < g_borderOffset && localPosition.y >= 0)
		{
			m_view.move(0, -deltaMove);
		}
		if (localPosition.x > m_resolution.x - g_borderOffset && localPosition.x <= m_resolution.x)
		{
			m_view.move(deltaMove, 0);
		}
		if (localPosition.y > m_resolution.y - g_borderOffset && localPosition.y <= m_resolution.y)
		{
			m_view.move(0, deltaMove);
		}

		/*
		if view position is out of field
			normalize position
		*/
		sf::Vector2f viewPosition = m_view.getCenter();
		sf::Vector2f viewSize = m_view.getSize();

		viewPosition.x = std::max(viewSize.x / 2, std::min(m_fieldSize.x - viewSize.x / 2, viewPosition.x));
		viewPosition.y = std::max(viewSize.y / 2, std::min(m_fieldSize.y - viewSize.y / 2, viewPosition.y));

		/*
		update view for window
		*/
		m_view.setCenter(viewPosition);
		m_window.setView(m_view);
	}
}

void ViewManager::mouseWheelScrolled(float delta)
{
	const float deltaModifier = -100.f;
	m_scaleFactor = std::max(m_minScaleFactor, std::min(m_maxScaleFactor, m_scaleFactor + delta / deltaModifier));
	m_view.setSize(m_viewInitialSize * m_scaleFactor);
}
