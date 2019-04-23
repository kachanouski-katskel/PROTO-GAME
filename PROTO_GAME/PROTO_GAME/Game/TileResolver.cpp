#include "TIleResolver.h"

namespace ProtoGame
{
	std::map<TTileType, TilePermissions> TileResolver::m_tileTypePermissions = {
		{TTileType::TT_DEFAULT, {true, true, true}},
		{TTileType::TT_TOWER, {false, false, true}},
		{TTileType::TT_BASTION, {false, false, true}},
		{TTileType::TT_WALL, {false, false, false}},
	};

	const TilePermissions TileResolver::getTilePermissions(Tile * tile)
	{
		if (tile == nullptr || m_tileTypePermissions.find(tile->getType()) == m_tileTypePermissions.end())
		{
			return { true, true, true };
		}
		
		return m_tileTypePermissions[tile->getType()];
	}
}
