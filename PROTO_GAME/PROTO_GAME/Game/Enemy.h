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
		float m_moveSpeed = 0.0f;
		float m_attackRadius = 0.0f;

		float m_attackTimer = 0.0f;
		float m_attackCooldown = 0.0f;
		bool m_canAttackNow = true;

	public:
		EnemyUnit(Vec2F startPos);
		virtual ~EnemyUnit();

		void TryAttack(HPChecker* other);
		virtual void onUpdate(double dt);

		BaseEnemyStrategy* getStrategy() const;
		void MoveTo(Vec2F pos, double dt);
		float getMoveSpeed() const;
		float getAttackRadius() const;
	};
}