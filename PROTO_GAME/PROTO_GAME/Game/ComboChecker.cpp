#include "ComboChecker.h"
#include "Field.h"

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

	void ComboChecker::addOnField(int iShift, int jShift, Vec2I lastAddPos, Combo combo, std::shared_ptr<Tower>& tower) const
	{
		Vec2I position = lastAddPos - Vec2I(iShift, jShift);
		int cols = combo.size;
		int rows = combo.comboShape.size() / combo.size;

		tower->setPosition(m_field->getCoordsByPosition(position));
		m_field->placeBigTile(tower, position, cols, rows);
	}

	ComboChecker::ComboChecker(Field * field)
		: m_field(field)
	{
		initCombos();
	}

	std::shared_ptr<Tower> ComboChecker::performCheck(Vec2I lastAddPosition, ITowerBallAddable* towerBallAddable) const
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
						std::shared_ptr<Tower> tower = std::make_shared<Tower>(towerBallAddable);
						addOnField(i, j, lastAddPosition, combo, tower);
						return tower;
					}
				}
			}
		}

		return nullptr;
	}


}
