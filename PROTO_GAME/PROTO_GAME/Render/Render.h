#pragma once
#include <vector>
#include <memory>

namespace sf
{
	class RenderWindow;
}

namespace ProtoGame {
	class DisplayObject;
	class Render {
	private:
		std::vector<DisplayObject*> m_renderObjects;
		
		static Render* g_instance;
		static sf::RenderWindow* g_window;

		Render();
		~Render();
	public:
		void update();

		void addChild(DisplayObject* object);
		void removeChild(DisplayObject* object);

		static Render* getInstance();
		static void destroyInstance();
		static void initWindow(sf::RenderWindow * window);
	};
}
