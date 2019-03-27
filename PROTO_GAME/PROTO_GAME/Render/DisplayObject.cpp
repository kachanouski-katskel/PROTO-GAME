#include "DisplayObject.h"
#include "Render.h"

#include <SFML/Graphics.hpp>

using namespace ProtoGame;

DisplayObject::DisplayObject(sf::Sprite* sprite)
	: m_sprite(sprite)
{
	Render::getInstance()->addChild(this);
}

ProtoGame::DisplayObject::DisplayObject(sf::Texture* texture)
{
	m_sprite = new sf::Sprite(*texture);
	Render::getInstance()->addChild(this);
}

DisplayObject::~DisplayObject()
{
	Render::getInstance()->removeChild(this);
	delete m_sprite;
}

void DisplayObject::setVisible(bool visible)
{
	m_visible = visible;
}

void ProtoGame::DisplayObject::setColor(int r, int g, int b)
{
	m_sprite->setColor(sf::Color(r, g, b, m_sprite->getColor().a));
}

void DisplayObject::setRotation(float rotation)
{
	m_rotation = rotation;
	if (m_sprite != nullptr)
	{
		m_sprite->setRotation(m_rotation);
	}
}

void DisplayObject::setAlpha(float alpha)
{
	m_alpha = alpha;
	if (m_sprite != nullptr)
	{
		sf::Color color = m_sprite->getColor();
		m_sprite->setColor(sf::Color(color.r, color.g, color.b, (int)(m_alpha * 256)));
	}
}

void DisplayObject::setPosition(const Vec2F& position)
{
	m_position = position;
	if (m_sprite != nullptr)
	{
		m_sprite->setPosition(sf::Vector2f(m_position.mPosX, m_position.mPosY));
	}
}

void DisplayObject::setScale(float scale) 
{
	m_scale = scale;
	if (m_sprite != nullptr) 
	{
		m_sprite->setScale(sf::Vector2f(m_scale, m_scale));
	}
}

bool DisplayObject::isVivible() const
{
	return m_visible;
}

sf::Sprite * ProtoGame::DisplayObject::getSprite() const
{
	return m_sprite;
}

float DisplayObject::getAlpha() const
{
	return 1.0f * m_sprite->getColor().a / 256;
}

float DisplayObject::getRotation() const
{
	return m_sprite->getRotation();
}

float DisplayObject::getScale() const
{
	return m_sprite->getScale().x;
}

Vec2F DisplayObject::getPosition() const
{
	return Vec2F(m_sprite->getPosition().x, m_sprite->getPosition().y);
}