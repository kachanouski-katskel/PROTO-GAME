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

	class GoldController
	{
	private:
		int m_goldAmount = 0;
	public:
		GoldController();
		virtual ~GoldController();
		virtual bool canUseGold(int amount) const;
		virtual void useGold(int amount);
		virtual void addGold(int amount);
	};

	class GameBase
	{
	private:
		int m_buildCost = 0;
		bool m_finished = false;

		std::vector<Tile*> m_tiles;
		std::shared_ptr<ArmyState> m_userArmy;
		std::shared_ptr<ArmyState> m_enemyArmy;
		std::shared_ptr<GoldController> m_userGoldController;
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
		GoldController* getGoldController(const ArmyState* state) const;
		Field* getField() const;
	};
}
