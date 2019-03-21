#pragma once
#include "../Render/DisplayObject.h"

namespace ProtoGame
{
	enum class TTileType
	{
		TT_DEFAULT,
		TT_TOWER,
		TT_WALL,
	};


	class Tile : public DisplayObject
	{
	private:
		TTileType mType = TTileType::TT_DEFAULT;

		void swapTexture(TTileType type);
	public:
		Tile();
		void SetType(TTileType type);
		virtual ~Tile();
	};
}

