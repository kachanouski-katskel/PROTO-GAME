#include "BattleStrategy.h"
#include "Bastion.h"
#include "ArmyState.h"
#include "Field.h"
#include "Tower.h"
#include "Enemy.h"
#include "TIleResolver.h"
#include "CloudObject.h"
#include "Random.h"
#include <algorithm>
#include <utility>
#include <queue>
#include <unordered_map>
#include <map>
#include <chrono>
#include <iostream>
#include <string>
using namespace ProtoGame;

static const float EPS = 0.00001;
static const float MODEL_SIZE = 10.0f; 

static inline int __hash(const std::pair<int, int>& pair, int hashSize) {
	return pair.first * hashSize + pair.second;
}

static inline std::pair<int, int> __dehash(int hash, int hashSize) {
	return std::make_pair(hash / hashSize, hash % hashSize);
}

static float getCloudProp()
{
	int hand = uniformRand(0, 1);
	int choice = uniformRand(0, 1275);
	int cur = 0;
	int curSum = 0;
	while (curSum < choice)
	{
		cur++;
		curSum += cur;
	}
	float offset = 1.0 * cur / 50;
	return offset * (hand ? -1 : 1);
}

std::vector<Vec2F> getControlPoints(Vec2I start, Vec2I end, const Field* field)
{
	std::queue<int> q;
	std::vector<int> p(10000, -1);
	int hashSize = field->getWidth();

	q.push(__hash({ start.mPosX, start.mPosY }, hashSize));
	std::vector<std::pair<int, int>> masks = {
		{ -1, 0},
		{ 1, 0},
		{ 0, -1},
		{ 0, 1}
	};
	std::vector<std::pair<int, int>> diagMasks = {
		{ -1, -1},
		{ 1, 1},
		{-1, 1},
		{1, -1}
	};
	std::vector<int> ans;
	p[q.front()] = 0;
	while (!q.empty()) 
	{
		auto curHash = q.front();
		q.pop();
		if (curHash == __hash({end.mPosX, end.mPosY}, hashSize)) {
			auto next = p[curHash];
			while (next != 0) {
				ans.push_back(next);
				next = p[next];
			}
			break;
		}
		bool useDiagMasks = true;
		for (int i = 0; i < masks.size(); i++) {
			auto to_ = __dehash(curHash, hashSize);
			auto to = std::make_pair(to_.first + masks[i].first, to_.second + masks[i].second);
			Tile* tile = field->getFieldTile(Vec2I(to.first, to.second));
			bool canStep = TileResolver::getTilePermissions(tile).canStepOn;
			if (p[__hash(to, hashSize)] == -1) {
				if (canStep)
				{
					p[__hash(to, hashSize)] = curHash;
					q.push(__hash(to, hashSize));
				}
				else
				{
					useDiagMasks = false;
				}
			}
		}
		if (useDiagMasks)
		{
			for (int i = 0; i < diagMasks.size(); i++) {
				auto to_ = __dehash(curHash, hashSize);
				auto to = std::make_pair(to_.first + diagMasks[i].first, to_.second + diagMasks[i].second);
				Tile * tile = field->getFieldTile(Vec2I(to.first, to.second));
				bool canStep = TileResolver::getTilePermissions(tile).canStepOn;
				if (canStep && p[__hash(to, hashSize)] == -1) {
					p[__hash(to, hashSize)] = curHash;
					q.push(__hash(to, hashSize));
				}
			}
		}
	}
	ans.pop_back();
	std::vector<Vec2F> ansVec;
	std::transform(
		ans.begin(),
		ans.end(),
		std::back_inserter(ansVec),
		[hashSize, field](int hash) 
		{
			auto pos = __dehash(hash, hashSize);
			Vec2F point = field->getCoordsByPosition({ pos.first, pos.second });
			return Vec2F(point.mPosX + field->getTileSize() / 2, point.mPosY + field->getTileSize() / 2);
		}
	);

		
	return ansVec;
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
		field->getPositionByCoords(unit->getPosition()), 
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
	if (!object->CanUpgrade())
	{
		return;
	}	
	bool found = false;
	int counter = 0;
	while (!found && counter < 11)
	{
		float angle = M_PI * (1.0f + getCloudProp());
		Vec2F dist = (state->getBastion()->getPosition() - object->getPosition()).getNormalVec();
		Vec2F new_ = dist.rotate(angle) * object->getMaxRadius();
		Vec2I position = field->getPositionByCoords(object->getPosition() + new_);
		if (TileResolver::getTilePermissions(field->getFieldTile(position)).canStepOn
			|| counter == 10)
		{
			found = true;
			object->ExpandCloud(field->getCoordsByPosition(position));
		}
		else
		{
			counter++;
		}
	}
}
