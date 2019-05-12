#pragma once
#include "../Render/DisplayObject.h"
#include "../Render/Vec2.h"

#include <vector>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>


namespace ProtoGame
{
	class HPBar : public DisplayObject
	{
	private:
		const float m_backgroundWidth = 50.f;
		const float m_backgroundHeight = 10.f;

		std::shared_ptr<sf::RectangleShape> m_barBackground = nullptr;
		std::shared_ptr<sf::RectangleShape> m_barInner = nullptr;

		float m_maxHp = 0;
		float m_currentHp = 0;

		void recalculateBarSizes();
	public:
		HPBar();

		void setMaxHp(const float & maxHP);
		void setHp(const float & HP);

		virtual void setPosition(const Vec2F & position) override;
		virtual Vec2F getPosition() const override;
		virtual std::vector<sf::Drawable*> getDrawables() const override;
	};
}
