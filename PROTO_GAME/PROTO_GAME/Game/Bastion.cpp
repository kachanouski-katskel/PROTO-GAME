#include "Bastion.h"
#include "GameInterfaces.h"
#include "Enemy.h"
#include <cassert>

using namespace ProtoGame;

Bastion::Bastion(IUnitAddable* unitAddable) :
	BattleObject(TTileType::TT_BASTION, ZOrder::Z_BASTION),
	m_unitAddable(unitAddable)
{
	setHP(30);
	setMaxHP(getHP());

	setVisible(true);

	m_unitCreatitonTimer = 9.0f;
	m_unitCreationRepeat = 10.0f;
}

Bastion::~Bastion()
{
}

void Bastion::onUpdate(double dt)
{
	m_unitCreatitonTimer += dt;
	if (m_unitCreatitonTimer >= m_unitCreationRepeat)
	{
		createUnit();
		m_unitCreatitonTimer = 0.0f;
	}
}

void Bastion::createUnit()
{
	assert(m_unitAddable != nullptr);
	if (m_unitAddable != nullptr)
	{
		m_unitAddable->AddUnit(std::make_shared<EnemyUnit>(getPosition()));
	}
}