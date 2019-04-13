#include "BattleStrategy.h"
#include "Bastion.h"
#include "ArmyState.h"

void ProtoGame::BaseEnemyMoveStrategy::MakeMove(EnemyUnit * unit, const ArmyState * state, double dt)
{
	Vec2F pos = state->getBastion()->getPosition();
	unit->MoveTo(pos, dt);
}
