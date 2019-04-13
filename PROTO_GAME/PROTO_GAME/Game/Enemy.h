#pragma once
#include "../Game/HpChecker.h"
#include "../Game/Tile.h"
#include "../Game/BattleStrategy.h"

#include <memory>

namespace ProtoGame
{
	class BaseEnemyStrategy;

	class EnemyUnit :
		public HPChecker,
		public Tile
	{
	private:
		std::unique_ptr<BaseEnemyStrategy> m_strategy;
		int m_attackPower = 0;
		int m_moveSpeed = 0.0f;
	public:
		EnemyUnit();
		virtual ~EnemyUnit();

		void Attack(HPChecker* other);
		virtual void onUpdate(double dt);

		BaseEnemyStrategy* getStrategy() const;
		void MoveTo(Vec2F pos, double dt);
	};
}