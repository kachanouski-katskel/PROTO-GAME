#pragma once
#include <vector>
#include <memory>
#include "Building.h"
#include "../Render/Vec2.h"

namespace ProtoGame
{
	class ArmyState;
	class Field;

	class ComboChecker
	{
	public:
		enum class ComboBlockType
		{
			CBT_ANY,
			CBT_SIMPLE
		};

		struct Combo
		{
			TTileType comboResult;
			int size;
			std::vector<ComboBlockType> comboShape;
		};

	private:
		std::vector<Combo> m_combosToCheck;
		Field* m_field;

		void initCombos();
		bool applyMask(int iShift, int jShift, Vec2I lastAddPos, Combo combo) const;
		void addOnField(int iShift, int jShift, Vec2I lastAddPos, Combo combo, std::shared_ptr<Building>& building) const;
		std::shared_ptr<Building> createBuilding(Combo combo, ArmyState* armyState) const;
	public:
		ComboChecker(Field * field);

		std::shared_ptr<Building> performCheck(Vec2I lastAddPosition, ArmyState* towerBallAddable) const;
	};
}
