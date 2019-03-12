#include "DisplayObject.h"

#include <SFML/Graphics.hpp>

using namespace ProtoGame;

DisplayObject::DisplayObject(sf::Sprite* sprite)
	: m_sprite(sprite)
{
}

ProtoGame::DisplayObject::DisplayObject(sf::Texture* texture)
{
	m_sprite = new sf::Sprite(*texture);
}

DisplayObject::~DisplayObject()
{
	delete m_sprite;
}

void DisplayObject::setVisible(bool visible)
{
	m_visible = visible;
}

void DisplayObject::setRotation(float rotation)
{
	m_rotation = rotation;
}

void DisplayObject::setAlpha(float alpha)
{
	m_alpha = alpha;
}

void DisplayObject::setScale(float scale) 
{
	m_scale = scale;
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
	return m_alpha;
}

float DisplayObject::getRotation() const
{
	return m_rotation;
}

float DisplayObject::getScale() const
{
	return m_scale;
}