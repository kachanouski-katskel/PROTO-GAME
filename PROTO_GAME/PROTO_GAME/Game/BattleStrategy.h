#pragma once

namespace ProtoGame
{
	class ArmyState;
	class EnemyUnit;
	class Tower;
	
	class BaseEnemyStrategy
	{
	public:
		virtual void MakeMove(EnemyUnit* unit, const ArmyState* state) = 0;
		virtual ~BaseEnemyStrategy() {};
	};

	class BaseTowerStrategy
	{
	public:
		virtual void MakeMove(Tower* tower, const ArmyState* state) = 0;
		virtual ~BaseTowerStrategy() {};
	};
}