#pragma once
#include "Bastion.h"
#include "ComboChecker.h"
#include <vector>

namespace ProtoGame
{
	class Tile;
	class Field;
	class EnemyUnit;
	class ArmyState;

	class GameBase
	{
	private:
		bool m_finished = false;

		std::vector<Tile*> m_tiles;
		std::shared_ptr<ArmyState> m_userArmy;
		std::shared_ptr<ArmyState> m_enemyArmy;

		std::unique_ptr<ComboChecker> m_comboChecker;
		Field* m_field;
	public:
		GameBase();
		virtual ~GameBase();

		virtual void Init();

		virtual void MouseDown(int x, int y);
		virtual void MouseUp(int x, int y);
		virtual void MouseMoved(int x, int y);

		virtual void Update(double dt);

		bool isFinished() const;
		void setFinished(bool value);

		Vec2F getFieldSize() const;

		const ArmyState* getOppositeArmy(const ArmyState* state) const;
		Field* getField() const;
	};
}
