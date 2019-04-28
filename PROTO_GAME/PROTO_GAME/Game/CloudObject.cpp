#include "CloudObject.h"
#include "BattleStrategy.h"
#include "GameInterfaces.h"
#include "Field.h"

using namespace ProtoGame;

CloudObject::CloudObject(ICloudAddable* cloudAddable, Vec2F position):
	BattleObject(TTileType::TT_CLOUD),
	m_cloudAddable(cloudAddable)
{
	setVisible(true);
	setPosition(position);
	m_hp = 100.0f;
	m_strategy = std::make_shared<SimpleCloudExpansionStrategy>();
	setAlpha(0.5f);
	m_startRadius = 20.0f;
	m_maxRadius = 30.0f;
	m_baseMoveTime = 2.0f;
	setInitialScale(m_startRadius * Field::m_tileSize / getSize().mPosX);
	setScale(m_initialScale);
}

CloudObject::~CloudObject()
{
}

void CloudObject::setInitialScale(float scale)
{
	m_initialScale = scale;
}

bool CloudObject::CanUpgrade() const
{
	return m_currentMoveTime >= getUpgradeTime();
}

float ProtoGame::CloudObject::getMaxRadius() const
{
	return m_maxRadius;
}

float CloudObject::getUpgradeTime() const
{
	return powf(m_ExpansionLevel, 3.0f) * m_baseMoveTime;
}

void CloudObject::ExpandCloud(Vec2F posToExpand)
{
	m_cloudAddable->AddCloud(std::make_shared<CloudObject>(m_cloudAddable, posToExpand));
	m_ExpansionLevel++;
	m_currentMoveTime = 0.0f;	
}

void CloudObject::onUpdate(double dt)
{
	m_currentMoveTime += dt;
	if (m_currentMoveTime >= getUpgradeTime())
	{
		return;
	}
	float tween = m_currentMoveTime / getUpgradeTime();
	float scale = 1.0f + tween * (m_maxRadius / m_startRadius - 1);
	setScale(m_initialScale * scale);
}

BaseCloudExpansionStrategy* CloudObject::getStrategy() const
{
	return m_strategy.get();
}
