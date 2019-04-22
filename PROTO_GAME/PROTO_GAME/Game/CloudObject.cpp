#include "CloudObject.h"
#include "BattleStrategy.h"
#include "GameInterfaces.h"

using namespace ProtoGame;

CloudObject::CloudObject(ICloudAddable* cloudAddable): 
	BattleObject(TTileType::TT_CLOUD),
	m_cloudAddable(cloudAddable)
{
	setVisible(true);
	m_hp = 100.0f;
	m_strategy = std::make_shared<SimpleCloudExpansionStrategy>();
	setAlpha(0.5f);
	//setScale()
}

CloudObject::~CloudObject()
{
}

void CloudObject::onUpdate(double dt)
{

}

BaseCloudExpansionStrategy* CloudObject::getStrategy() const
{
	return m_strategy.get();
}
