#pragma once
#include "../Game/HpChecker.h"
#include "../Game/Tile.h"

#include <memory>

namespace ProtoGame
{
	class AttackStrategy;

	class EnemyUnit :
		public HPChecker,
		public Tile
	{
	private:
		std::unique_ptr<AttackStrategy> m_strategy;
		int m_attackPower = 0;
	public:
		EnemyUnit();
		virtual ~EnemyUnit();

		void Attack(HPChecker* other);
	};
}