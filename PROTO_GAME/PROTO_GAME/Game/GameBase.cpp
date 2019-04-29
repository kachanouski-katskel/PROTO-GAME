#include "GameBase.h"
#include "Tile.h"
#include "Field.h"
#include "ArmyState.h"

#include <memory>
using namespace ProtoGame;

const ArmyState * ProtoGame::GameBase::getOppositeArmy(const ArmyState* state) const
{
	if (state == m_enemyArmy.get()) 
	{
		return m_userArmy.get();
	}
	return m_enemyArmy.get();
}

Field * ProtoGame::GameBase::getField() const
{
	return m_field;
}

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
}

void GameBase::Init()
{
	m_field = new Field();
	m_comboChecker = std::make_unique<ComboChecker>(m_field);
	m_userArmy = std::make_shared<ArmyState>(this, false);
	m_enemyArmy = std::make_shared<ArmyState>(this, true);
}

void GameBase::MouseDown(int x, int y)
{
}

void GameBase::MouseUp(int x, int y)
{	
	Vec2I pos = m_field->getPositionByCoords(Vec2F(x, y));
	bool placed = m_field->placeBuildingBlock(pos);
	if (placed)
	{
		std::shared_ptr<Tower> tower = m_comboChecker->performCheck(pos, m_userArmy.get());
		if (tower != nullptr)
		{
			m_userArmy->AddTower(tower);
		}
	}
}

void ProtoGame::GameBase::MouseMoved(int x, int y)
{
	Vec2I pos = m_field->getPositionByCoords(Vec2F(x, y));
	m_field->highlightPosition(pos);
}

void GameBase::Update(double dt)
{
	if (m_enemyArmy->getBastion()->isDead() || m_userArmy->getBastion()->isDead())
	{
		m_finished = true;
		return;
	}
	m_enemyArmy->onUpdate(dt);
	m_userArmy->onUpdate(dt);
}

bool ProtoGame::GameBase::isFinished() const
{
	return m_finished;
}

void ProtoGame::GameBase::setFinished(bool value)
{
	m_finished = value;
}
