#pragma once

#include <vector>
#include "../Render/Vec2.h"

namespace ProtoGame
{
	class Tile;

	class Field
	{
	protected:
		const Vec2I m_fieldSize = Vec2I(100, 80);
		int m_tileSize = 8;
		Vec2F m_fieldOffset = Vec2F(0.f, 0.f);

		Tile* m_highlightTile = nullptr;

		std::vector<std::vector<Tile*>> m_fieldData;

	public:
		Field();
		virtual ~Field();

		Vec2F getCoordsByPosition(Vec2I position);
		Vec2I getPositionByCoords(Vec2F coords);
		void highlightPosition(Vec2I position);
	};
}
