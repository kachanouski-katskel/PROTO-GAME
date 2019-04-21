#include "ArmyState.h"
#include "Tower.h"
#include "Enemy.h"
#include "GameBase.h"
#include "Field.h"

#include <vector>
#include <memory>
#include <algorithm>

using namespace ProtoGame;

ArmyState::ArmyState(GameBase* game, bool isEnemy)
	: m_game(game)
{
	m_bastion = std::make_shared<Bastion>(this);
	Vec2I bastionPos = isEnemy ? Vec2I(80, 70) : Vec2I(10, 10);
	Vec2F fPos = game->getField()->getCoordsByPosition(bastionPos);
	m_bastion->setFieldPosition(bastionPos);
	m_bastion->setPosition(fPos);
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

Bastion* ProtoGame::ArmyState::getBastion() const
{
	return m_bastion.get();
}

void ArmyState::onUpdate(double dt)
{
	m_bastion->onUpdate(dt);
	std::vector<Tower*> towersToDelete;
	std::vector<EnemyUnit*> unitsToDelete;
	for (const auto& tower : m_towers)
	{
		if (tower->isDead())
		{
			towersToDelete.push_back(tower.get());
			continue;
		}
		tower->Update(dt);
	}
	for (auto& unit : m_units)
	{
		if (unit->isDead())
		{
			unitsToDelete.push_back(unit.get());
			continue;
		}
		auto strategy = unit->getStrategy();
		strategy->MakeMove(unit.get(), m_game->getOppositeArmy(this), m_game->getField(), dt);
		unit->onUpdate(dt);
	}
	m_towers.erase(
		std::remove_if(m_towers.begin(), m_towers.end(), 
			[towersToDelete](const auto& tower)
			{
				return std::find(towersToDelete.begin(), towersToDelete.end(), tower.get()) != towersToDelete.end();
			}), 
		m_towers.end()
	);

	m_units.erase(
		std::remove_if(m_units.begin(), m_units.end(),
			[unitsToDelete](const auto& unit)
			{
				return std::find(unitsToDelete.begin(), unitsToDelete.end(), unit.get()) != unitsToDelete.end();
			}),
		m_units.end()
	);
}
