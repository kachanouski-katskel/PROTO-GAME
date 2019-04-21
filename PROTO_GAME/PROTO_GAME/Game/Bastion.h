#pragma once
#include "../Game/BattleObject.h"
#include <memory>

namespace ProtoGame
{
	class IUnitAddable;

	class Bastion :
		public BattleObject
	{
	private:
		float m_unitCreationRepeat = 0.0f;
		float m_unitCreatitonTimer = 0.0f;

		IUnitAddable* m_unitAddable = nullptr;
	public:
		Bastion(IUnitAddable* unitAddable);
		virtual ~Bastion();

		virtual void createUnit();
		virtual void onUpdate(double dt);
	};
}
