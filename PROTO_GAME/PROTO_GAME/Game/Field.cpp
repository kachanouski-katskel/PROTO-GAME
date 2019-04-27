#include "Field.h"
#include "Tile.h"
#include "../Render/Vec2.h"
#include "TIleResolver.h"
#include "../Storage/TextureStorage.h"
#include <cmath>

using namespace ProtoGame;


Field::Field()
{
	m_fieldData.resize(m_fieldSize.mPosX);
	m_background = std::make_shared<FieldBackground>(m_tileSize * m_fieldSize.mPosY, m_tileSize * m_fieldSize.mPosX);

	for (int i = 0, xLength = m_fieldSize.mPosX; i < xLength; i++)
	{
		m_fieldData[i].resize(m_fieldSize.mPosY);
		for (int j = 0, yLength = m_fieldSize.mPosY; j < yLength; j++)
		{
			// Walls around
			m_fieldData[i][j] = nullptr;
			if (i < 2 || j < 2 || xLength - i <= 2 || yLength - j <= 2)
			{
				m_fieldData[i][j] = std::make_shared<Tile>(TTileType::TT_WALL);
			}

			// Lake in center
			const int lakeRadius = 20;
			if (pow(lakeRadius, 2) >= pow((i - m_fieldSize.mPosX / 2 + 1), 2) + pow((j - m_fieldSize.mPosY / 2 + 1), 2))
			{
				m_fieldData[i][j] = std::make_shared<Tile>(TTileType::TT_WATER);
			}

			if (m_fieldData[i][j] != nullptr)
			{
				m_fieldData[i][j]->setFieldPosition(Vec2I(i, j));
				m_fieldData[i][j]->setVisible(true);
				m_fieldData[i][j]->setPosition(getCoordsByPosition(m_fieldData[i][j]->getFieldPosition()));
			}
		}
	}

	m_highlightTile = std::make_unique<Tile>(TTileType::TT_HIGHLIGHT, ZOrder::Z_HIGHLIGHT);
	m_highlightTile->setAlpha(0.5f);
}

Field::~Field()
{
}

Vec2F Field::getCoordsByPosition(Vec2I position) const
{
	return Vec2F(m_fieldOffset.mPosX + position.mPosY * m_tileSize, m_fieldOffset.mPosY + position.mPosX * m_tileSize);
}

Vec2I Field::getPositionByCoords(Vec2F coords) const
{
	return Vec2I((int)(coords.mPosY - m_fieldOffset.mPosY) / m_tileSize, (int)(coords.mPosX - m_fieldOffset.mPosX) / m_tileSize);
}

void Field::highlightPosition(Vec2I position)
{
	m_highlightTile->setVisible(true);
	std::shared_ptr<Tile> tile = m_fieldData[position.mPosX][position.mPosY];
	m_highlightTile->setPosition(getCoordsByPosition(position));
	if (TileResolver::getTilePermissions(tile.get()).canBuildOn)
	{
		m_highlightTile->setColor(0, 255, 0);
	}
	else
	{
		m_highlightTile->setColor(255, 0, 0);
	}
}

Tile* Field::getFieldTile(Vec2I position) const
{
	return m_fieldData[position.mPosX][position.mPosY].get();
}

void Field::placeBuildingBlock(Vec2I position)
{
	std::shared_ptr<Tile> tile = m_fieldData[position.mPosX][position.mPosY];
	if (TileResolver::getTilePermissions(tile.get()).canBuildOn)
	{
		addTileToField(TTileType::TT_TOWER, position);
		//m_fieldData[position.mPosX][position.mPosY] = std::make_shared<Tile>(TTileType::TT_TOWER);
	}
}

FieldBackground::FieldBackground(int width, int height) : ProtoGame::DisplayObject(new sf::Sprite())
{
	sf::Texture& ground = TextureStorage::getInstance()->getTexture("ground");
	ground.setRepeated(true);
	m_sprite->setTexture(ground);
	m_sprite->setTextureRect({ 0, 0, width, height });
	setVisible(true);
}

void Field::addTileToField(TTileType type, Vec2I position)
{
	const int x = position.mPosX;
	const int y = position.mPosY;
	m_fieldData[x][y] = std::make_shared<Tile>(type);
	m_fieldData[x][y]->setFieldPosition(position);
	m_fieldData[x][y]->setVisible(true);
	m_fieldData[x][y]->setPosition(getCoordsByPosition(position));
}
