#include "Enemy.h"

using namespace ProtoGame;

EnemyUnit::EnemyUnit() 
	: Tile(TTileType::TT_ENEMY)
{
	m_moveSpeed = 0.001f;
	m_strategy.reset(new BaseEnemyMoveStrategy());
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::Attack(HPChecker* checker)
{
}

void EnemyUnit::onUpdate(double dt)
{
	m_strategy->MakeMove(this, nullptr, dt);
}

BaseEnemyStrategy * ProtoGame::EnemyUnit::getStrategy() const
{
	return m_strategy.get();
}

void ProtoGame::EnemyUnit::MoveTo(Vec2F pos, double dt)
{
	Vec2F direction = getPosition().getNormalVec();
	Vec2F deltaVec = direction * (dt * m_moveSpeed);
	setPosition(getPosition() + deltaVec);
}
