#include "BattleObject.h"

using namespace ProtoGame;

BattleObject::BattleObject(TTileType type, ZOrder zOrder /*= ZOrder::Z_DEFAULT*/)
	: Tile(type, zOrder)
{
}

void ProtoGame::BattleObject::setPosition(const Vec2F & position)
{
	ProtoGame::Tile::setPosition(position);
	setHpBarPosition({ position.mPosX, position.mPosY });
}

float BattleObject::getAttackPower() const
{
	return m_attackPower * getAttackScale();
}

int BattleObject::getGoldCost() const
{
	return 0;
}
