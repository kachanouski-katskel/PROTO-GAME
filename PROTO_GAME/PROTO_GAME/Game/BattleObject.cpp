#include "BattleObject.h"

using namespace ProtoGame;

BattleObject::BattleObject(TTileType type)
	: Tile(type)
{
}

void ProtoGame::BattleObject::setPosition(const Vec2F & position)
{
	ProtoGame::Tile::setPosition(position);
	setHpBarPosition({ position.mPosX, position.mPosY });
}
