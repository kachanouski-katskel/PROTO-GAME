#pragma once
#include "../Game/HpChecker.h"
#include "../Game/Tile.h"
#include "Enemy.h"
#include <memory>

namespace ProtoGame
{
	class IUnitAddable
	{
	public:
		virtual void AddUnit(std::shared_ptr<EnemyUnit> unit) = 0;
	};

	class Bastion :
		public HPChecker,
		public Tile
	{
	private:
		float m_unitCreationRepeat = 0.0f;
		float m_unitCreatitonTimer = 0.0f;

		std::shared_ptr<IUnitAddable> m_unitAddable;
	public:
		Bastion(IUnitAddable* unitAddable);
		virtual ~Bastion();

		virtual void createUnit();
		virtual void onUpdate(double dt);
	};
}
