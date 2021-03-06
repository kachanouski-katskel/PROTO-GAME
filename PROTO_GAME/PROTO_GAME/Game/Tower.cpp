#include "Tower.h"
#include "TowerBall.h"
#include "GameInterfaces.h"
#include "BattleStrategy.h"
#include <cassert>

using namespace ProtoGame;

Tower::Tower(ITowerBallAddable* ballAddable) :
	Building(TTileType::TT_TOWER),
	m_towerBallAddable(ballAddable)
{
	setVisible(true);
	setHP(10.0f);
	setMaxHP(getHP());

	m_attackDelay = 3.0f;
	m_attackPower = 2.0f;
	m_attackRadius = 100.0f;

	m_strategy = std::make_shared<EnemyTowerStrategy>();
}

Tower::~Tower()
{
}

void Tower::TryAttack(std::shared_ptr<BattleObject> target)
{
	if (m_canAttackNow)
	{
		if ((target->getPosition() - getPosition()).len() < m_attackRadius)
		{
			std::shared_ptr<TowerBall> ball = std::make_shared<TowerBall>(target, getAttackPower(), getPosition(), m_ballType);
			assert(m_towerBallAddable != nullptr);
			if (m_towerBallAddable != nullptr)
			{
				m_towerBallAddable->AddBall(ball);
			}
			m_attackTimer = 0.0f;
			m_canAttackNow = false;
		}
	}
}

void Tower::Update(double dt)
{
	m_attackTimer += dt;
	if (m_attackTimer >= m_attackDelay)
	{
		m_attackTimer = 0.0f;
		m_canAttackNow = true;
	}
}

int Tower::getGoldCost() const
{
	return 100;
}


//////////////////////////////////////////////////////////////


CloudTower::CloudTower(ITowerBallAddable * ballAddable):
	Tower(ballAddable)
{
	setVisible(true);
	setHP(500.0f);
	setMaxHP(getHP());

	m_attackDelay = 3.0f;
	m_attackPower = 8.0f;
	m_attackRadius = 200.0f;

	m_ballType = TTileType::TT_TOWER_CLOUD_BALL;

	m_strategy = std::make_shared<CloudTowerStrategy>();
}

CloudTower::~CloudTower()
{
}

int CloudTower::getGoldCost() const
{
	return 20;
}
