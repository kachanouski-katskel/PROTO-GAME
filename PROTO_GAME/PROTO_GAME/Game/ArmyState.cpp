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
	m_bastion->setFieldPosition({ 50, 50 });
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

const VecShared<EnemyUnit>& ArmyState::getUnits() const
{
	return m_units;
}

const VecShared<Tower>& ArmyState::getTowers() const
{
	return m_towers;
}

const Bastion* ProtoGame::ArmyState::getBastion() const
{
	return m_bastion.get();
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
		auto strategy = unit->getStrategy();
		strategy->MakeMove(unit.get(), this, dt);
		unit->onUpdate(dt);
	}
}
