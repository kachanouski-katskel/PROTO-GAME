#include "HPBar.h"

void ProtoGame::HPBar::recalculateBarSizes()
{
	if (m_maxHp > 0)
	{
		const float ratio = m_currentHp / m_maxHp;
		m_barInner->setSize({ ratio * m_backgroundWidth, m_backgroundHeight });
		if (ratio > .75f)
		{
			m_barInner->setFillColor({ 0, 255, 0, 200 });
		}
		else if (ratio > 0.25f)
		{
			m_barInner->setFillColor({ 255, 255, 0, 200 });
		}
		else
		{
			m_barInner->setFillColor({ 255, 0, 0, 200 });
		}
	}
}

ProtoGame::HPBar::HPBar() : ProtoGame::DisplayObject(static_cast<sf::Sprite*>(nullptr))
{
	m_barBackground = std::make_shared<sf::RectangleShape>();
	m_barInner = std::make_shared<sf::RectangleShape>();
	m_barBackground->setSize({ m_backgroundWidth, m_backgroundHeight });
	m_barBackground->setOrigin({ m_backgroundWidth / 2, m_backgroundHeight * 2 });
	m_barInner->setOrigin({ m_backgroundWidth / 2, m_backgroundHeight * 2 });
	m_barBackground->setFillColor({ 0, 0, 0, 200 });
	m_barInner->setFillColor({ 0, 255, 0, 200 });
}

void ProtoGame::HPBar::setMaxHp(const float & maxHP)
{
	m_maxHp = maxHP;
	recalculateBarSizes();
}

void ProtoGame::HPBar::setHp(const float & HP)
{
	m_currentHp = HP;
	recalculateBarSizes();
}

void ProtoGame::HPBar::setPosition(const Vec2F & position)
{
	m_barBackground->setPosition({ position.mPosX, position.mPosY });
	m_barInner->setPosition({ position.mPosX, position.mPosY });
}

ProtoGame::Vec2F ProtoGame::HPBar::getPosition() const
{
	return Vec2F(m_barBackground->getPosition().x, m_barBackground->getPosition().y);
}

std::vector<sf::Drawable*> ProtoGame::HPBar::getDrawables() const
{
	return std::vector<sf::Drawable*>{m_barInner.get()};
}
