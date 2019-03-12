#include "DisplayObject.h"

using namespace ProtoGame;

DisplayObject::DisplayObject(void* sprite)
	: m_sprite(sprite)
{
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