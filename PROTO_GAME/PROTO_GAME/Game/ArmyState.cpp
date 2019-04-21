#include "ArmyState.h"
#include "Tower.h"
#include "Enemy.h"
#include "GameBase.h"
#include "Field.h"
#include "TowerBall.h"

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
	if (!isEnemy)
	{
		std::shared_ptr<Tower> tower = std::make_shared<Tower>(this);
		Vec2I towerPos = Vec2I(75, 50);
		Vec2F tPos = game->getField()->getCoordsByPosition(towerPos);
		tower->setFieldPosition(towerPos);
		tower->setPosition(tPos);
		m_towers.push_back(tower);
	}
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

void ArmyState::AddBall(std::shared_ptr<TowerBall> ball)
{
	m_towerBalls.push_back(std::move(ball));
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

std::shared_ptr<Bastion> ProtoGame::ArmyState::getBastion() const
{
	return m_bastion;
}

void ArmyState::onUpdate(double dt)
{
	if (m_bastion->isDead())
	{
		return;
	}
	m_bastion->onUpdate(dt);

	std::vector<Tower*> towersToDelete;
	std::vector<EnemyUnit*> unitsToDelete;
	std::vector<TowerBall*> ballsToDelete;
	for (const auto& ball : m_towerBalls)
	{
		if (ball->getIsDead())
		{
			ballsToDelete.push_back(ball.get());
			continue;
		}
		ball->Update(dt);
	}
	for (const auto& tower : m_towers)
	{
		if (tower->isDead())
		{
			towersToDelete.push_back(tower.get());
			continue;
		}
		tower->Update(dt);
		auto strategy = tower->getStrategy();
		strategy->MakeMove(tower.get(), m_game->getOppositeArmy(this), m_game->getField(), dt);
	}
	for (auto& unit : m_units)
	{
		if (unit->isDead())
		{
			unitsToDelete.push_back(unit.get());
			continue;
		}
		unit->onUpdate(dt);
		auto strategy = unit->getStrategy();
		strategy->MakeMove(unit.get(), m_game->getOppositeArmy(this), m_game->getField(), dt);
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

	m_towerBalls.erase(
		std::remove_if(m_towerBalls.begin(), m_towerBalls.end(),
			[ballsToDelete](const auto& ball)
		{	
			return std::find(ballsToDelete.begin(), ballsToDelete.end(), ball.get()) != ballsToDelete.end();
		}),
		m_towerBalls.end()
	);
}
