#include "Enemy.h"
#include "BattleStrategy.h"

#include <cmath>
#include <cassert>

using namespace ProtoGame;

EnemyUnit::EnemyUnit(Vec2F startPos) 
	: BattleObject(TTileType::TT_ENEMY, ZOrder::Z_UNIT)
{
	m_moveSpeed = 50.f;
	m_attackCooldown = 5.0f;
	m_attackRadius = Vec2F(getSize().mPosX / 2, getSize().mPosY / 2).len() + 1.0f;

	m_attackPower = 4;
	setHP(10);
	setMaxHP(getHP());

	m_strategy = std::make_shared<BaseEnemyMoveStrategy>();
	setVisible(true);
	setPosition(startPos);
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::TryAttack(HPChecker* checker)
{
	if (m_canAttackNow)
	{
		checker->removeHP(getAttackPower());
		m_attackTimer = 0.0f;
		m_canAttackNow = false;
	}
}

void EnemyUnit::onUpdate(double dt)
{
	m_attackTimer += dt;
	if (m_attackTimer >= m_attackCooldown)
	{
		m_attackTimer = 0.0f;
		m_canAttackNow = true;
	}
}

BaseEnemyStrategy * ProtoGame::EnemyUnit::getStrategy() const
{
	return m_strategy.get();
}

void ProtoGame::EnemyUnit::MoveTo(Vec2F pos, double dt)
{
	Vec2F distVec = pos - getPosition();
	distVec = distVec.getNormalVec();
	setPosition(pos);
	if (abs(distVec.mPosY) < 0.03)
	{
		setRotation(90.f * (distVec.mPosX > 0 ? 1 : -1));
	}
	else
	{
		setRotation(-(atan(distVec.mPosX / distVec.mPosY) / (acos(-1)) * 180.f + (distVec.mPosX < 0 ? 180.f : 0.f) + 180.f));
	}
}

float ProtoGame::EnemyUnit::getMoveSpeed() const
{
	return m_moveSpeed;
}

float ProtoGame::EnemyUnit::getAttackRadius() const
{
	return m_attackRadius;
}
