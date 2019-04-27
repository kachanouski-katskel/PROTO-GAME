#pragma once
#include "../Render/DisplayObject.h"

namespace ProtoGame
{
	enum class TTileType
	{
		TT_DEFAULT,
		TT_TOWER,
		TT_WALL,
		TT_WATER,
		TT_ENEMY,
		TT_HIGHLIGHT,
		TT_TOWER_BALL,
		TT_CLOUD,
		TT_BASTION
	};


	class Tile : public DisplayObject
	{
	private:
		TTileType mType = TTileType::TT_DEFAULT;
		Vec2I m_fieldPosition = Vec2I(0, 0);

		void swapTexture(TTileType type);		
	public:
		Tile(ZOrder zOrder = ZOrder::Z_DEFAULT);
		Tile(TTileType type, ZOrder zOrder = ZOrder::Z_DEFAULT);
		virtual ~Tile();

		TTileType getType() const;

		void SetType(TTileType type);

		void setFieldPosition(Vec2I position);
		Vec2I getFieldPosition() const;
	};
}

