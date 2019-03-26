#pragma once
#include "../Render/DisplayObject.h"

namespace ProtoGame
{
	enum class TTileType
	{
		TT_DEFAULT,
		TT_TOWER,
		TT_WALL,
		TT_ENEMY
	};


	class Tile : public DisplayObject
	{
	private:
		TTileType mType = TTileType::TT_DEFAULT;

		void swapTexture(TTileType type);
	public:
		Tile();
		Tile(TTileType type);
		virtual ~Tile();

		TTileType getType() const;

		void SetType(TTileType type);
	};
}

