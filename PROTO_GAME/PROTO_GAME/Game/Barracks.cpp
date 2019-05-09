#include "Barracks.h"
#include "GameInterfaces.h"
#include "BattleStrategy.h"
#include "Enemy.h"
#include <cassert>

namespace ProtoGame
{
	Barracks::Barracks(IUnitAddable * unitAddable)
		: Building(TTileType::TT_BARRACKS),
		m_unitAddable(unitAddable)
	{
		setVisible(true);
		setHP(10.f);
		setMaxHP(getHP());

		m_unitCreatitonTimer = 0.f;
		m_unitCreationRepeat = 10.f;

		m_strategy = std::make_shared<BarracksStrategy>();
	}

	void Barracks::TryCreateUnit()
	{
		assert(m_unitAddable != nullptr);
		if (m_canCreateUnitNow)
		{
			if (m_unitAddable != nullptr)
			{
				m_unitAddable->AddUnit(std::make_shared<EnemyUnit>(getPosition() - Vec2F{10.f, 10.f})); // hack. TODO: try fix
			}
			m_canCreateUnitNow = false;
			m_unitCreatitonTimer = 0.f;
		}
	}

	void Barracks::Update(double dt)
	{
		m_unitCreatitonTimer += dt;
		if (m_unitCreatitonTimer >= m_unitCreationRepeat)
		{
			m_unitCreatitonTimer = 0.f;
			m_canCreateUnitNow = true;
		}
	}
}
