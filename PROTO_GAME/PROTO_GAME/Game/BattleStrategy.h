#pragma once

namespace ProtoGame
{
	class ArmyState;
	class EnemyUnit;
	class Tower;
	class Field;
	
	class BaseEnemyStrategy
	{
	public:
		virtual void MakeMove(EnemyUnit* unit, const ArmyState* state, const Field* field, double dt) = 0;
		virtual BaseEnemyStrategy* getStrategy() { return this; }
		virtual ~BaseEnemyStrategy() {};
	};	

	class BaseEnemyMoveStrategy :
		public BaseEnemyStrategy
	{
		// move to the closest bastion;
	public:
		void MakeMove(EnemyUnit* unit, const ArmyState* state, const Field* field, double dt) override;
	};

	class BaseTowerStrategy
	{
	public:
		virtual void MakeMove(Tower* tower, const ArmyState* state, const Field* field, double dt) = 0;
		virtual ~BaseTowerStrategy() {};
	};
}