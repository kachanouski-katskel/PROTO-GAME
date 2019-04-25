#pragma once
#include "BattleObject.h"
#include <memory>

namespace ProtoGame
{
	class BaseCloudExpansionStrategy;
	class ICloudAddable;

	struct CloudInfo 
	{
		int m_level = 1;
		float m_baseUpgradeTime = 5.0f;
		float m_currentUpgradeTime = 0.0f;

		void CanUpgrade();
		void getTween();
		void Update(double dt);
	};
	
	class CloudObject :
		public BattleObject
	{
	private:
		float m_maxRadius = 0.0f;
		float m_startRadius = 0.0f;
		float m_moveTime = 0.0f;
		float m_currentMoveTime = 0.0f;

		std::shared_ptr<BaseCloudExpansionStrategy> m_strategy;
		ICloudAddable* m_cloudAddable = nullptr;
	public:
		CloudObject(ICloudAddable* cloudAddable);
		~CloudObject();

		virtual void onUpdate(double dt);

		BaseCloudExpansionStrategy* getStrategy() const;
	};
}