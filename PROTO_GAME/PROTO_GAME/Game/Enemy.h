#pragma once
#include "../Game/BattleObject.h"
#include <memory>

namespace ProtoGame
{
	class BaseEnemyStrategy;

	class EnemyUnit :
		public BattleObject
	{
	private:
		std::shared_ptr<BaseEnemyStrategy> m_strategy;
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