#include "Field.h"
#include "Tile.h"
#include "../Render/Vec2.h"
#include "TIleResolver.h"


ProtoGame::Field::Field()
{
	m_fieldData.resize(m_fieldSize.mPosY);
	for (int i = 0, yLength = m_fieldSize.mPosY; i < yLength; i++)
	{
		m_fieldData[i].resize(m_fieldSize.mPosX);
		for (int j = 0, xLength = m_fieldSize.mPosX; j < xLength; j++)
		{
			m_fieldData[i][j] = nullptr;
			if (i < 2 || j < 2 || xLength - j <= 2 || yLength - i <= 2)
			{
				m_fieldData[i][j] = new Tile(TTileType::TT_WALL);
				m_fieldData[i][j]->setFieldPosition(Vec2I(j, i));
				m_fieldData[i][j]->setVisible(true);
			}

			if (m_fieldData[i][j] != nullptr)
			{
				m_fieldData[i][j]->setPosition(getCoordsByPosition(m_fieldData[i][j]->getFieldPosition()));
			}
		}
	}

	m_highlightTile = new Tile(TTileType::TT_HIGHLIGHT);
	m_highlightTile->setAlpha(0.5f);
}

ProtoGame::Field::~Field()
{
}

ProtoGame::Vec2F ProtoGame::Field::getCoordsByPosition(Vec2I position) const
{
	return Vec2F(m_fieldOffset.mPosX + position.mPosX * m_tileSize, m_fieldOffset.mPosY + position.mPosY * m_tileSize);
}

ProtoGame::Vec2I ProtoGame::Field::getPositionByCoords(Vec2F coords) const
{
	return Vec2I((int)(coords.mPosX - m_fieldOffset.mPosX) / m_tileSize, (int)(coords.mPosY - m_fieldOffset.mPosY) / m_tileSize);
}

void ProtoGame::Field::highlightPosition(Vec2I position)
{
	m_highlightTile->setVisible(true);
	Tile* tile = m_fieldData[position.mPosY][position.mPosX];
	m_highlightTile->setPosition(getCoordsByPosition(position));
	if (TileResolver::getTilePermissions(tile).canBuildOn)
	{
		m_highlightTile->setColor(0, 255, 0);
	}
	else
	{
		m_highlightTile->setColor(255, 0, 0);
	}
}
