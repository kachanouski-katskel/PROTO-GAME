#pragma once
#include "BattleObject.h"
#include <memory>

namespace ProtoGame
{
	class BaseCloudExpansionStrategy;
	class ICloudAddable;
	
	class CloudObject :
		public BattleObject
	{
	private:
		float m_maxRadius = 0.0f;
		float m_startRadius = 0.0f;

		int m_ExpansionLevel = 1;
		float m_baseMoveTime = 0.0f;
		float m_currentMoveTime = 0.0f;

		float m_initialScale = 1.0f;

		std::shared_ptr<BaseCloudExpansionStrategy> m_strategy;
		ICloudAddable* m_cloudAddable = nullptr;

		void setInitialScale(float scale);
	public:
		CloudObject(ICloudAddable* cloudAddable, Vec2F position);
		~CloudObject();

		bool CanUpgrade() const;
		float getMaxRadius() const;
		virtual float getUpgradeTime() const;
		virtual void ExpandCloud(Vec2F posToExpand);

		virtual void onUpdate(double dt);

		BaseCloudExpansionStrategy* getStrategy() const;
	};
}