#include "Tile.h"
#include "../Storage/TextureStorage.h"
#include <iostream>
using namespace ProtoGame;

//TODO
sf::Sprite* temp = nullptr;

void ProtoGame::Tile::swapTexture(TTileType type)
{
	if (type == TTileType::TT_WALL)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("wall"));
	}
	else if (type == TTileType::TT_WATER)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("water"));
		setScale(1.f / 4.f);
	}
	else if (type == TTileType::TT_HIGHLIGHT)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("highlight"));
	}
	else if (type == TTileType::TT_ENEMY)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("enemy_unit"));
		setScale(1.f / 4.f);
		m_sprite->setOrigin({ m_sprite->getTexture()->getSize().x / 2.f, m_sprite->getTexture()->getSize().y / 2.f });
	}
	else if (type == TTileType::TT_TOWER_ENEMY_BALL)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("ball"));
		setScale(16.0f / getSize().mPosX);
		m_sprite->setOrigin({ m_sprite->getTexture()->getSize().x / 2.f, m_sprite->getTexture()->getSize().y / 2.f });
	}
	else if (type == TTileType::TT_TOWER_CLOUD_BALL)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("ice_ball"));
		setScale(16.0f / getSize().mPosX);
		m_sprite->setOrigin({ m_sprite->getTexture()->getSize().x / 2.f, m_sprite->getTexture()->getSize().y / 2.f });
	}
	else if (type == TTileType::TT_TOWER)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("tower"));
	}
	else if (type == TTileType::TT_BUILDING_BLOCK)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("wall"));
	}
	else if (type == TTileType::TT_CLOUD)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("cloud"));
		setScale(1.f);
		m_sprite->setOrigin({ m_sprite->getTexture()->getSize().x / 2.f, m_sprite->getTexture()->getSize().y / 2.f });
	}
	else if (type == TTileType::TT_BARRACKS)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("barracks"));
	}
	else if (type == TTileType::TT_BASTION)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("bastion"));
		setScale(1.f / 1.5f);
	}
}

Tile::Tile(ZOrder zOrder /* = ZOrder::Z_DEFAULT */) : DisplayObject(new sf::Sprite(), zOrder)
{
}

Tile::Tile(TTileType type, ZOrder zOrder /* = ZOrder::Z_DEFAULT */)
	: Tile(zOrder)
{
	SetType(type);
}

TTileType ProtoGame::Tile::getType() const
{
	return mType;
}

void ProtoGame::Tile::SetType(TTileType type)
{
	mType = type;
	swapTexture(mType);
}

void Tile::setFieldPosition(Vec2I position)
{
	m_fieldPosition = position;
}

Vec2I Tile::getFieldPosition() const
{
	return m_fieldPosition;
}

Tile::~Tile()
{

}