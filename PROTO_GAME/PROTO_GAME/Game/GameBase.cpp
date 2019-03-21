#include "GameBase.h"
#include "Tile.h"

using namespace ProtoGame;

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
}

void GameBase::Init()
{
	wall = new Tile();
	wall->SetType(TTileType::TT_WALL);
	wall->setVisible(true);
}

void GameBase::MouseDown(int x, int y)
{
}

void GameBase::MouseUp(int x, int y)
{
}

void GameBase::Update(double dt)
{
	CheckEvents();
}

void GameBase::CheckEvents()
{
}
