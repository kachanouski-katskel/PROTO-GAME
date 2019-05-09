#pragma once
#include "BattleObject.h"

#include <memory>


namespace ProtoGame
{
	class BaseBuildingStrategy;

	class Building :
		public BattleObject
	{
	protected:
		std::shared_ptr<BaseBuildingStrategy> m_strategy;

	public:
		Building(TTileType type, ZOrder zOrder = ZOrder::Z_DEFAULT);

		BaseBuildingStrategy* getStrategy() const;
		virtual void Update(double dt) = 0;
	};
}
