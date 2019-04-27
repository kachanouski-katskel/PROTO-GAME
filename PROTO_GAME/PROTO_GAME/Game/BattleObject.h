#pragma once
#include "HpChecker.h"
#include "Tile.h"


namespace ProtoGame
{

	class BattleObject:
		public HPChecker,
		public Tile
	{
	public:
		BattleObject(TTileType type, ZOrder zOrder = ZOrder::Z_DEFAULT);

		virtual void setPosition(const Vec2F & position) override;
	};
}