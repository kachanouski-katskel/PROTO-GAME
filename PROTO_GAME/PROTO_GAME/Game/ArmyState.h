#pragma once
#include "Bastion.h"

#include <vector>
#include <memory>

namespace ProtoGame
{
	template<class T>
	using VecShared = std::vector<std::shared_ptr<T>>;

	class Tower;
	class EnemyUnit;
	class Bastion;
	class GameBase;

	class ArmyState :
		public IUnitAddable
	{
	private:
		std::vector<std::shared_ptr<EnemyUnit>> m_units;
		std::vector<std::shared_ptr<Tower>> m_towers;
		std::shared_ptr<Bastion> m_bastion;

		GameBase* m_game = nullptr;
	public:
		ArmyState(GameBase* game, bool isEnemy);
		virtual ~ArmyState();

		virtual void AddUnit(std::shared_ptr<EnemyUnit> unit) override;
		void AddTower(std::shared_ptr<Tower> tower);

		virtual void onUpdate(double dt);

		const VecShared<EnemyUnit>& getUnits() const;
		const VecShared<Tower>& getTowers() const;
		Bastion* getBastion() const;
	};
}
