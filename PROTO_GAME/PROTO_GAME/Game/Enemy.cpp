#include "Enemy.h"
#include <cmath>

using namespace ProtoGame;

EnemyUnit::EnemyUnit() 
	: Tile(TTileType::TT_ENEMY)
{
	m_moveSpeed = 10.f;
	m_strategy.reset(new BaseEnemyMoveStrategy());
	setVisible(true);
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::Attack(HPChecker* checker)
{
}

void EnemyUnit::onUpdate(double dt)
{
	//m_strategy->MakeMove(this, nullptr, dt);
}

BaseEnemyStrategy * ProtoGame::EnemyUnit::getStrategy() const
{
	return m_strategy.get();
}

void ProtoGame::EnemyUnit::MoveTo(Vec2F pos, double dt)
{
	Vec2F distVec = pos - getPosition();
	float distance = distVec.len();
	if (distance > 1)
	{
		Vec2F direction = distVec.getNormalVec();
		Vec2F deltaVec = direction * (dt * m_moveSpeed);
		setPosition(getPosition() + deltaVec);
		setRotation(atan(distVec.mPosY / distVec.mPosX) / (acos(-1)) * 180.f * (distVec.mPosX < 0 ? -1 : 1));
	} 
	else
	{
		setPosition(Vec2F(100, 100));
	}
}
