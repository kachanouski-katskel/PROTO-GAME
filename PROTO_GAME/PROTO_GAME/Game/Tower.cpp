#include "Tower.h"

using namespace ProtoGame;

Tower::Tower()
	: Tile(TTileType::TT_TOWER)
{
}

Tower::~Tower()
{
}

bool Tower::isReadyAttack() const
{
	return m_attackDelay <= 0;
}

void Tower::Attack()
{
	m_attackDelay = 0.0f;
}

void Tower::Update(double dt)
{
	m_attackDelay -= dt;
}
