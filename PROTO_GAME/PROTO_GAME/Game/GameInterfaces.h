#pragma once
#include <memory>

namespace ProtoGame
{
	class EnemyUnit;
	class TowerBall;
	class CloudObject;

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

	class ICloudAddable
	{
	public:
		virtual void AddCloud(std::shared_ptr<CloudObject> cloud) = 0;
	};

}