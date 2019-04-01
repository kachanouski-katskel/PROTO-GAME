#include "Enemy.h"

using namespace ProtoGame;

EnemyUnit::EnemyUnit() 
	: Tile(TTileType::TT_ENEMY)
{
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::Attack(HPChecker* checker)
{
}