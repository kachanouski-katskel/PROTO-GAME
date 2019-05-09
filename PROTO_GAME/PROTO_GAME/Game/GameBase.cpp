#include "GameBase.h"
#include "Tile.h"
#include "Field.h"
#include "ArmyState.h"

#include <iostream>
#include <memory>
using namespace ProtoGame;

const ArmyState* GameBase::getOppositeArmy(const ArmyState* state) const
{
	if (state == m_enemyArmy.get()) 
	{
		return m_userArmy.get();
	}
	return m_enemyArmy.get();
}

GoldController* GameBase::getGoldController(const ArmyState* state) const
{
	if (state == m_enemyArmy.get())
	{
		return m_userGoldController.get();
	}
	return nullptr;
}

Field * GameBase::getField() const
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
	m_userGoldController = std::make_shared<GoldController>();
	m_buildCost = 20;
}

void GameBase::MouseDown(int x, int y)
{
}

void GameBase::MouseUp(int x, int y)
{	
	Vec2I pos = m_field->getPositionByCoords(Vec2F(x, y));
	if (!m_userGoldController->canUseGold(m_buildCost))
	{
		return;
	}
	bool placed = m_field->placeBuildingBlock(pos);
	if (placed)
	{
		m_userGoldController->useGold(m_buildCost);
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
	if (pos.mPosY >= 0 && pos.mPosY < m_field->getWidth() && pos.mPosX >= 0 && pos.mPosX < m_field->getHeight())
	{
		m_field->highlightPosition(pos);
	}
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

Vec2F ProtoGame::GameBase::getFieldSize() const
{
	return {m_field->getWidth() * m_field->getTileSize(), m_field->getHeight() * m_field->getTileSize()};
}

/////////////////////////////

GoldController::GoldController()
{
}

GoldController::~GoldController()
{
}

void GoldController::useGold(int amount)
{
	std::cout << "was: " << m_goldAmount << " now: " << m_goldAmount - amount << std::endl;
	m_goldAmount -= amount;
}

void GoldController::addGold(int amount)
{
	std::cout << "was: " << m_goldAmount << " now: " << m_goldAmount + amount << std::endl;
	m_goldAmount += amount;
}

bool GoldController::canUseGold(int amount) const
{
	return m_goldAmount >= amount;
}
