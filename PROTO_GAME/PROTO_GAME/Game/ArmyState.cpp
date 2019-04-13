#include "ArmyState.h"
#include "Tower.h"
#include "Enemy.h"

#include <vector>
#include <memory>
#include <algorithm>

using namespace ProtoGame;

ArmyState::ArmyState()
{
	m_bastion = std::make_shared<Bastion>(this);
}

ArmyState::~ArmyState()
{
}

void ArmyState::AddUnit(std::shared_ptr<EnemyUnit> unit)
{
	m_units.push_back(std::move(unit));
}

void ArmyState::AddTower(std::shared_ptr<Tower> tower)
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

void ArmyState::onUpdate(double dt)
{
	m_bastion->onUpdate(dt);
	for (auto& tower : m_towers)
	{
		tower->Update(dt);
	}
	for (auto& unit : m_units)
	{
		unit->onUpdate(dt);
	}
}