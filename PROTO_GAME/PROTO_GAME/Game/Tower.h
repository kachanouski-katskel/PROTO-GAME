#pragma once
#include "../Game/Tile.h"
#include "../Game/HpChecker.h"

namespace ProtoGame
{
	class Tower : 
		public Tile,
		public HPChecker
	{
	protected:
		float m_attackDelay = 0.0f;
	public:
		Tower();
		virtual ~Tower();

		bool isReadyAttack() const;

		virtual void Attack();
		virtual void Update(double dt);
	};

}
