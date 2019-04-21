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
		BattleObject(TTileType type);
	};
}