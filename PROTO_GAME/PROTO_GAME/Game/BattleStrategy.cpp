#include "BattleStrategy.h"
#include "Bastion.h"
#include "ArmyState.h"
#include "Field.h"
#include "Tower.h"
#include "Enemy.h"
#include <algorithm>
#include <utility>

using namespace ProtoGame;

static const float EPS = 0.00001;
static const float MODEL_SIZE = 10.0f;

std::vector<Vec2F> getControlPoints(Vec2I start, Vec2I end, const Field* field)
{
	return std::vector<Vec2F>();
}

std::shared_ptr<BattleObject> getNearestEnemy(Vec2F curPosition, const ArmyState* state, const Field* field, bool onlyUnits = false)
{
	VecShared<BattleObject> possibles;
	for (auto& enemy : state->getUnits())
	{
		possibles.emplace_back(enemy);
	}
	if (!onlyUnits)
	{
		for (auto& tower : state->getTowers())
		{
			possibles.emplace_back(tower);
		}
		possibles.emplace_back(state->getBastion());
	}
	std::sort(possibles.begin(), possibles.end(),
		[=](const auto& first, const auto& second)
		{
			return (curPosition - first->getPosition()).len() < (curPosition - second->getPosition()).len();
		}
	);
	if (possibles.empty())
	{
		return std::shared_ptr<BattleObject>();
	}
	return possibles.front();
}

void BaseEnemyMoveStrategy::MakeMove(EnemyUnit * unit, const ArmyState * state, const Field* field, double dt)
{
	auto enemyInfo = getNearestEnemy(unit->getPosition(), state, field, true);
	if (!enemyInfo)
		return;

	Vec2F enemyPos = enemyInfo->getPosition();
	Vec2F unitPos = unit->getPosition();

	float attackRadius = unit->getAttackRadius();
	if ((unitPos - enemyPos).len() <= attackRadius)
	{
		unit->TryAttack(enemyInfo.get());
		return;
	}


	float distanceLeft = unit->getMoveSpeed() * dt;
	std::vector<Vec2F> points = getControlPoints(
		field->getPositionByCoords(enemyPos),
		unit->getFieldPosition(), 
		field);
	points.insert(points.begin(), unitPos);
	points.push_back(enemyPos);

	int curPointIndex = 0;
	while (distanceLeft > EPS && curPointIndex != points.size() - 1)
	{
		Vec2F nextPoint = points[curPointIndex + 1];
		Vec2F curPoint = points[curPointIndex];
		Vec2F differenceVec = nextPoint - curPoint;

		if ((unit->getPosition() - enemyPos).len() <= MODEL_SIZE)
		{
			break;
		}

		float scale = std::min(distanceLeft / differenceVec.len(), 1.0f);
		Vec2F delta = differenceVec * scale;

		unit->MoveTo(unit->getPosition() + delta, dt);
		curPointIndex++;
		distanceLeft -= delta.len();
	}

	if ((unitPos - enemyPos).len() > attackRadius)
	{
		return;
	}


	unit->TryAttack(enemyInfo.get());
}

void EnemyTowerStrategy::MakeMove(Tower * tower, const ArmyState * state, const Field * field, double dt)
{
	auto enemyInfo = getNearestEnemy(tower->getPosition(), state, field, true);
	if (enemyInfo)
	{
		tower->TryAttack(enemyInfo);
	}
}

void SimpleCloudExpansionStrategy::MakeMove(CloudObject* object, const ArmyState* state, const Field* field, double dt)
{
}
