#pragma once
#include <vector>
#include <memory>

namespace ProtoGame
{
	template<class T>
	using VecShared = std::vector<std::shared_ptr<T>>;

	class Tower;
	class EnemyUnit;


	class ArmyState
	{
	private:
		std::vector<std::shared_ptr<EnemyUnit>> m_units;
		std::vector<std::shared_ptr<Tower>> m_towers;

	public:
		ArmyState();
		virtual ~ArmyState();

		void addUnit(std::shared_ptr<EnemyUnit> unit);
		void addTower(std::shared_ptr<Tower> tower);

		VecShared<EnemyUnit> getUnits() const;
		VecShared<Tower> getTowers() const;
	};
}
