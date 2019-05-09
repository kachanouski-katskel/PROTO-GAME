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
		const int m_maxExpansionLevel = 3;

		float m_maxDiam = 0.0f;
		float m_startDiam = 0.0f;

		int m_ExpansionLevel = 1;
		float m_baseMoveTime = 0.0f;
		float m_currentMoveTime = 0.0f;

		float m_initialScale = 1.0f;

		float m_attackScale = 1.0f;
		float m_defenceScale = 1.0f;

		std::shared_ptr<BaseCloudExpansionStrategy> m_strategy;
		ICloudAddable* m_cloudAddable = nullptr;

		void setInitialScale(float scale);
	public:
		CloudObject(ICloudAddable* cloudAddable, Vec2F position);
		~CloudObject();

		bool CanUpgrade() const;
		float getMaxDiam() const;
		float getCurrRadius() const;
		virtual float getUpgradeTime() const;
		virtual void ExpandCloud(Vec2F posToExpand);

		virtual void onUpdate(double dt);

		BaseCloudExpansionStrategy* getStrategy() const;

		float getAttackScale() const;
		float getDefenceScale() const;

		int getGoldCost() const override;
	};
}