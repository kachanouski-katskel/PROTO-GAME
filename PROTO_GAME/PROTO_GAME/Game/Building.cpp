#include "Building.h"

namespace ProtoGame
{
	Building::Building(TTileType type, ZOrder zOrder)
		: BattleObject(type, zOrder)
	{
	}

	BaseBuildingStrategy * Building::getStrategy() const
	{
		return m_strategy.get();
	}
}
