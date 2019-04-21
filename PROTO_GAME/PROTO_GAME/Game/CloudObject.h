#pragma once
#include "BattleObject.h"

namespace ProtoGame
{

	
	class CloudObject :
		public BattleObject
	{
	private:
		float m_maxRadius = 0.0f;
		float m_startRadius = 0.0f;
		float m_moveTime = 0.0f;
		float m_currentMoveTime = 0.0f;

		
	public:
		CloudObject();
		~CloudObject();

		virtual void onUpdate(double dt);
	};
}