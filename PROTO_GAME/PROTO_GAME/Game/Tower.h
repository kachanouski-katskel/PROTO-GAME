#pragma once
#include "../Game/BattleObject.h"
#include "../Game/BattleStrategy.h"
#include "../Game/Building.h"

#include <memory>

namespace ProtoGame
{
	class ITowerBallAddable;
	class BaseBuildingStrategy;

	class Tower : 
		public Building
	{
	protected:
		float m_attackDelay = 0.0f;
		float m_attackTimer = 0.0f;
		bool m_canAttackNow = true;

		float m_attackRadius = 0.0f;	
		TTileType m_ballType = TTileType::TT_TOWER_ENEMY_BALL;
		ITowerBallAddable* m_towerBallAddable = nullptr;

	public:
		Tower(ITowerBallAddable* ballAddable);
		virtual ~Tower();

		virtual void TryAttack(std::shared_ptr<BattleObject> target);
		virtual void Update(double dt) override;
		int getGoldCost() const override;
	};


	class CloudTower :
		public Tower
	{
	public:
		CloudTower(ITowerBallAddable* ballAddable);
		virtual ~CloudTower();

		int getGoldCost() const override;
	};

}
