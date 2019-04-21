#include "Bastion.h"

using namespace ProtoGame;

Bastion::Bastion(IUnitAddable* unitAddable) :
	Tile(TTileType::TT_BASTION)
{
	m_unitAddable = std::shared_ptr<IUnitAddable>(unitAddable);
	m_hp = 30;

	m_unitCreatitonTimer = 9.0f;
	m_unitCreationRepeat = 10.0f;
}

Bastion::~Bastion()
{
	m_unitAddable.reset();
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
	m_unitAddable->AddUnit(std::make_shared<EnemyUnit>(getPosition()));
}