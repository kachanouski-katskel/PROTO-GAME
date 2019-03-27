#include "GameBase.h"
#include "Tile.h"
#include "Field.h"

using namespace ProtoGame;

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
}

void GameBase::Init()
{
	m_field = new Field();
}

void GameBase::MouseDown(int x, int y)
{
}

void GameBase::MouseUp(int x, int y)
{
}

void ProtoGame::GameBase::MouseMoved(int x, int y)
{
	Vec2I pos = m_field->getPositionByCoords(Vec2F(x, y));
	m_field->highlightPosition(pos);
}

void GameBase::Update(double dt)
{
	CheckEvents();
}

void GameBase::CheckEvents()
{
}
