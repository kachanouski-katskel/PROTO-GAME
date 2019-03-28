#pragma once

namespace ProtoGame
{
	class ArmyState;
	
	class BattleStrategy
	{
		virtual void MakeMove(const ArmyState* state) = 0;
	};
}