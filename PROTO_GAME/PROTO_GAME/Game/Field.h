#pragma once

#include <vector>
#include "../Render/Vec2.h"
#include "../Render/DisplayObject.h"
#include <memory>

namespace ProtoGame
{
	class Tile;
	enum class TTileType;

	struct FieldBackground : public DisplayObject
	{
		FieldBackground(int width, int height);
	};

	class Field
	{		

	protected:
		std::shared_ptr<FieldBackground> m_background;

		const Vec2I m_fieldSize = Vec2I(80, 100);
		int m_tileSize = 8;
		Vec2F m_fieldOffset = Vec2F(0.f, 0.f);

		std::unique_ptr<Tile> m_highlightTile;

		std::vector<std::vector<std::shared_ptr<Tile>>> m_fieldData;

		void addTileToField(TTileType type, Vec2I position);

	public:
		Field();
		virtual ~Field();

		Vec2F getCoordsByPosition(Vec2I position) const;
		Vec2I getPositionByCoords(Vec2F coords) const;
		void highlightPosition(Vec2I position);
		Tile* getFieldTile(Vec2I position) const;
		void placeBuildingBlock(Vec2I position);
	};
}
