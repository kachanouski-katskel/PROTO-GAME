#pragma once
#include "HpChecker.h"
#include "Tile.h"


namespace ProtoGame
{

	class BattleObject:
		public HPChecker,
		public Tile
	{
	protected:
		float m_attackPower = 0.0f;
	public:
		BattleObject(TTileType type, ZOrder zOrder = ZOrder::Z_DEFAULT);

		virtual void setPosition(const Vec2F & position) override;
		virtual float getAttackPower() const;
	};
}