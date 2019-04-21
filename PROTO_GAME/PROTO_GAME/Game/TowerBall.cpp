#include "TowerBall.h"
#include <algorithm>
using namespace ProtoGame;

static const float EPS = 0.0001f;

TowerBall::TowerBall(std::shared_ptr<BattleObject> target, float attackPower, Vec2F startPos) : 
	Tile(TTileType::TT_TOWER_BALL), 
	m_target(target), 
	m_attackPower(attackPower)
{
	setPosition(startPos);
	setVisible(true);
}

TowerBall::~TowerBall()
{
}

void TowerBall::Update(double dt)
{
	if (m_isDead)
		return;

	auto target = m_target.lock();
	if (!target)
	{
		m_isDead = true;
		return;
	}
	
	Vec2F differenceVec = target->getPosition() - getPosition();
	float distanceCan = m_flySpeed * dt;
	float scale = std::min(distanceCan / differenceVec.len(), 1.0f);
	Vec2F delta = differenceVec * scale;

	setPosition(getPosition() + delta);
	setRotation(atan(differenceVec.mPosY / differenceVec.mPosX) / (acos(-1)) * 180.f * (differenceVec.mPosX < 0 ? -1 : 1));
	distanceCan -= delta.len();

	if (distanceCan < EPS)
	{
		m_isDead = true;
		target->removeHP(m_attackPower);
	}
}

bool TowerBall::getIsDead() const
{
	return m_isDead;
}
