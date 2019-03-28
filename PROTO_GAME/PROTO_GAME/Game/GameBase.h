#pragma once
#include <vector>

namespace ProtoGame
{
	class Tile;
	class Field;
	class GameBase {
	private:
		std::vector<Tile*> m_tiles;
		
		Field* m_field;
	public:
		GameBase();
		virtual ~GameBase();

		virtual void Init();

		virtual void MouseDown(int x, int y);
		virtual void MouseUp(int x, int y);
		virtual void MouseMoved(int x, int y);

		virtual void Update(double dt);
		virtual void CheckEvents();
	};
}
