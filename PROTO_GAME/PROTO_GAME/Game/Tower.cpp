#include "Tower.h"

using namespace ProtoGame;

Tower::Tower()
	: Tile(TTileType::TT_TOWER)
{
}

ProtoGame::Tower::~Tower()
{
}

bool ProtoGame::Tower::isReadyAttack() const
{
	return m_attackDelay <= 0;
}

void ProtoGame::Tower::Attack()
{
	m_attackDelay = 0.0f;
}

void ProtoGame::Tower::Update(double dt)
{
	m_attackDelay -= dt;
}
