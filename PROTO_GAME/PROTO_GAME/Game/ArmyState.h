#pragma once
#include "GameInterfaces.h"
#include <vector>
#include <memory>

namespace ProtoGame
{
	template<class T>
	using VecShared = std::vector<std::shared_ptr<T>>;

	class Building;
	class EnemyUnit;
	class Bastion;
	class GameBase;
	class TowerBall;
	class CloudObject;
	class BattleObject;

	class ArmyState :
		public IUnitAddable,
		public ITowerBallAddable,
		public ICloudAddable
	{
	private:
		std::vector<std::shared_ptr<EnemyUnit>> m_units;
		std::vector<std::shared_ptr<Building>> m_buildings;
		std::vector<std::shared_ptr<TowerBall>> m_towerBalls;
		std::vector<std::shared_ptr<CloudObject>> m_clouds;
		std::shared_ptr<Bastion> m_bastion;

		GameBase* m_game = nullptr;
	public:
		ArmyState(GameBase* game, bool isEnemy);
		virtual ~ArmyState();

		virtual void AddUnit(std::shared_ptr<EnemyUnit> unit) override;
		virtual void AddBall(std::shared_ptr<TowerBall> ball) override;
		virtual void AddCloud(std::shared_ptr<CloudObject> cloud) override;
		void AddBuilding(std::shared_ptr<Building> tower);

		virtual void onUpdate(double dt);
		virtual void onBattleObjectDead(const BattleObject* object);

		const VecShared<EnemyUnit>& getUnits() const;
		const VecShared<Building>& getBuildings() const;
		const VecShared<CloudObject> getClouds() const;
		std::shared_ptr<Bastion> getBastion() const;
	};
}
