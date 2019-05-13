#pragma once

namespace ProtoGame
{
	class ArmyState;
	class EnemyUnit;
	class Tower;
	class Field;
	class CloudObject;
	class Building;
	
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

	class BaseBuildingStrategy
	{
	public:
		virtual void MakeMove(Building* tower, const ArmyState* state, const Field* field, double dt) = 0;
		virtual ~BaseBuildingStrategy() {};
	};

	class EnemyTowerStrategy:
		public BaseBuildingStrategy
	{
	public:
		void MakeMove(Building* tower, const ArmyState* state, const Field* field, double dt) override;
	};

	class CloudTowerStrategy :
		public BaseBuildingStrategy
	{
	public:
		void MakeMove(Building* tower, const ArmyState* state, const Field* field, double dt) override;
	};

	class BarracksStrategy :
		public BaseBuildingStrategy
	{
	public:
		void MakeMove(Building* tower, const ArmyState* state, const Field* field, double dt) override;
	};

	class BaseCloudExpansionStrategy
	{
	public:
		virtual void MakeMove(CloudObject* object, const ArmyState* state, const Field* field, double dt) = 0;
		virtual ~BaseCloudExpansionStrategy() {};
	};

	class SimpleCloudExpansionStrategy:
		public BaseCloudExpansionStrategy
	{
		void MakeMove(CloudObject* object, const ArmyState* state, const Field* field, double dt) override;
	};
}