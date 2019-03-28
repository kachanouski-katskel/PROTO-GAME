#include "ArmyState.h"
#include <vector>
#include <memory>

using namespace ProtoGame;

ProtoGame::ArmyState::ArmyState()
{
}

ProtoGame::ArmyState::~ArmyState()
{
}

void ProtoGame::ArmyState::addUnit(std::shared_ptr<EnemyUnit> unit)
{
	m_units.push_back(std::move(unit));
}

void ProtoGame::ArmyState::addTower(std::shared_ptr<Tower> tower)
{
	m_towers.push_back(std::move(tower));
}

VecShared<EnemyUnit> ArmyState::getUnits() const
{
	return m_units;
}

VecShared<Tower> ArmyState::getTowers() const
{
	return m_towers;
}
