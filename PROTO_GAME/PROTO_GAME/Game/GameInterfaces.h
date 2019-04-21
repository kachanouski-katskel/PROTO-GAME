#pragma once
#include <memory>

namespace ProtoGame
{
	class EnemyUnit;
	class TowerBall;

	class IUnitAddable
	{
	public:
		virtual void AddUnit(std::shared_ptr<EnemyUnit> unit) = 0;
	};

	class ITowerBallAddable
	{
	public:
		virtual void AddBall(std::shared_ptr<TowerBall> ball) = 0;
	};
}