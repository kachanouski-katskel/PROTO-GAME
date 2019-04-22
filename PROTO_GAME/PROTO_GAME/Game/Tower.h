#pragma once
#include "../Game/BattleObject.h"
#include "../Game/BattleStrategy.h"

#include <memory>

namespace ProtoGame
{
	class ITowerBallAddable;
	class BaseTowerStrategy;

	class Tower : 
		public BattleObject
	{
	private:
		std::shared_ptr<BaseTowerStrategy> m_strategy;

	protected:
		float m_attackDelay = 0.0f;
		float m_attackTimer = 0.0f;
		bool m_canAttackNow = true;

		float m_attackRadius = 0.0f;
		float m_attackPower = 0.0f;		

		ITowerBallAddable* m_towerBallAddable = nullptr;

	public:
		Tower(ITowerBallAddable* ballAddable);
		virtual ~Tower();

		virtual void TryAttack(std::shared_ptr<BattleObject> target);
		virtual void Update(double dt);

		BaseTowerStrategy* getStrategy() const;
	};

}
