#pragma once
#include <memory>
#include "BattleObject.h"

namespace ProtoGame
{
	class Enemy;

	class TowerBall :
		public Tile
	{
	private:
		float m_flySpeed = 0.0f;
		float m_attackPower = 0.0f;
		
		bool m_isDead = false;
		std::weak_ptr<BattleObject> m_target;

	public:
		TowerBall(std::shared_ptr<BattleObject> target, float m_attackPower, Vec2F startPos);
		~TowerBall();

		void Update(double dt);
		bool getIsDead() const;
	};
}