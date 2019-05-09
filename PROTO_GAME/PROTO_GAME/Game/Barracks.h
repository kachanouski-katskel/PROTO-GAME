#pragma once

#include "Building.h"


namespace ProtoGame
{
	class IUnitAddable;

	class Barracks :
		public Building
	{
	protected:
		float m_unitCreationRepeat = 0.0f;
		float m_unitCreatitonTimer = 0.0f;

		bool m_canCreateUnitNow = false;

		IUnitAddable* m_unitAddable = nullptr;

	public:
		Barracks(IUnitAddable* unitAddable);

		virtual void TryCreateUnit();
		virtual void Update(double dt) override;
	};
}
