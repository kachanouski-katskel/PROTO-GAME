#pragma once
#include <map>

#include "Tile.h"


namespace ProtoGame
{
	struct TilePermissions
	{
		bool canStepOn = true;
		bool canBuildOn = true;
		bool canFlyOver = true;
	};

	class TileResolver
	{
		static std::map<TTileType, TilePermissions> m_tileTypePermissions;
	public:
		TileResolver() = delete;
		TileResolver(const TileResolver&) = delete;

		static const TilePermissions getTilePermissions(Tile* tile);
	};

}