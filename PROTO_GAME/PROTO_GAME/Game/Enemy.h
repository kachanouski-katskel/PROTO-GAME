#pragma once
#include "../Game/HpChecker.h"
#include "../Game/Tile.h"

namespace ProtoGame
{
	class EnemyStrategy
	{
		virtual void MakeMove() = 0;
	};

	class EnemyUnit :
		public HPChecker,
		public Tile
	{
	private:
		EnemyStrategy* m_strategy = nullptr;
		int m_attackPower = 0;
	public:
		EnemyUnit();
		virtual ~EnemyUnit();

		void Attack(HPChecker* other);
	};
}