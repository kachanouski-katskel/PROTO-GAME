#include "Tile.h"
#include "../Storage/TextureStorage.h"

using namespace ProtoGame;

//TODO
sf::Sprite* temp = nullptr;

void ProtoGame::Tile::swapTexture(TTileType type)
{
	if (type == TTileType::TT_WALL)
	{
		m_sprite->setTexture(TextureStorage::getInstance()->getTexture("wall"));
	}
}

Tile::Tile() : DisplayObject(new sf::Sprite())
{
}

Tile::Tile(TTileType type)
	: Tile()
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

Tile::~Tile()
{

}