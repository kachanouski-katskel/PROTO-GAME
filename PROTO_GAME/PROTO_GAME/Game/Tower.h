#pragma once
#include "../Game/Tile.h"
#include "../Game/HpChecker.h"
#include "../Game/BattleStrategy.h"

#include <memory>

namespace ProtoGame
{
	class Tower : 
		public Tile,
		public HPChecker
	{
	private:
		std::unique_ptr<BaseTowerStrategy> m_strategy;

	protected:
		float m_attackDelay = 0.0f;

	public:
		Tower();
		virtual ~Tower();

		bool isReadyAttack() const;

		virtual void Attack();
		virtual void Update(double dt);
	};

}
