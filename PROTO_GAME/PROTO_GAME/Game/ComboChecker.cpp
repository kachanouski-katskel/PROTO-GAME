#include "ComboChecker.h"
#include "ArmyState.h"
#include "Field.h"
#include "Barracks.h"
#include "Tower.h"

#include <cassert>

namespace ProtoGame
{
	void ComboChecker::initCombos()
	{
		m_combosToCheck.emplace_back(
			Combo {
				TTileType::TT_TOWER, 3,
				{
				ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,
				ComboBlockType::CBT_SIMPLE, ComboBlockType::CBT_ANY,	ComboBlockType::CBT_SIMPLE,
				ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE
				}
			}
		);

		m_combosToCheck.emplace_back(
			Combo {
				TTileType::TT_BARRACKS, 4,
				{
				ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,
				ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_ANY,	ComboBlockType::CBT_ANY,	ComboBlockType::CBT_SIMPLE,
				ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_ANY,	ComboBlockType::CBT_ANY,	ComboBlockType::CBT_SIMPLE,
				ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE,	ComboBlockType::CBT_SIMPLE
				}
			}
		);
	}

	bool ComboChecker::applyMask(int iShift, int jShift, Vec2I lastAddPos, Combo combo) const
	{
		Vec2I startPos = lastAddPos - Vec2I(iShift, jShift);
		int comboRowsCount = combo.comboShape.size() / combo.size;
		if (startPos.mPosX < 0 || startPos.mPosY < 0 || startPos.mPosY + combo.size >= m_field->getWidth() || startPos.mPosX + comboRowsCount >= m_field->getHeight())
		{
			return false;
		}

		for (int i = 0; i < comboRowsCount; i++)
		{
			for (int j = 0; j < combo.size; j++)
			{
				int index = i * combo.size + j;
				if (combo.comboShape[index] == ComboBlockType::CBT_ANY)
				{
					continue;
				}
				if (combo.comboShape[index] == ComboBlockType::CBT_SIMPLE)
				{
					Tile * tile = m_field->getFieldTile({ i + startPos.mPosX, j + startPos.mPosY });
					if (tile == nullptr || tile->getType() != TTileType::TT_BUILDING_BLOCK)
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	void ComboChecker::addOnField(int iShift, int jShift, Vec2I lastAddPos, Combo combo, std::shared_ptr<Building>& building) const
	{
		Vec2I position = lastAddPos - Vec2I(iShift, jShift);
		int cols = combo.size;
		int rows = combo.comboShape.size() / combo.size;

		building->setPosition(m_field->getCoordsByPosition(position));
		m_field->placeBigTile(building, position, cols, rows);
	}

	std::shared_ptr<Building> ComboChecker::createBuilding(Combo combo, ArmyState* armyState) const
	{
		std::shared_ptr<Building> result;
		if (combo.comboResult == TTileType::TT_BARRACKS)
		{
			result = std::make_shared<Barracks>(armyState);
		}
		else if (combo.comboResult == TTileType::TT_TOWER)
		{
			result = std::make_shared<Tower>(armyState);
		}
		else
		{
			assert(false);
		}
		return result;
	}

	ComboChecker::ComboChecker(Field * field)
		: m_field(field)
	{
		initCombos();
	}

	std::shared_ptr<Building> ComboChecker::performCheck(Vec2I lastAddPosition, ArmyState* armyState) const
	{
		for (Combo combo : m_combosToCheck)
		{
			int cols = combo.size;
			int rows = combo.comboShape.size() / combo.size;

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					bool applied = applyMask(i, j, lastAddPosition, combo);
					if (applied)
					{

						std::shared_ptr<Building> building = createBuilding(combo, armyState);
						addOnField(i, j, lastAddPosition, combo, building);
						return building;
					}
				}
			}
		}

		return nullptr;
	}


}
