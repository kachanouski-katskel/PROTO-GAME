#pragma once
#include <vector>
#include <memory>

namespace ProtoGame {
	class DisplayObject;
	class Render {
	private:
		std::vector<std::shared_ptr<DisplayObject>> m_renderObjects;
		
		static Render* g_instance;

		Render();
		~Render();
	public:
		void update();

		void addChild(DisplayObject* object);

		static Render* getInstance();
		static void destroyInstance();
	};
}
