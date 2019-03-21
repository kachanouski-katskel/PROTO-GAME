#pragma once
#include <SFML/Graphics.hpp>

namespace ProtoGame
{
	class TextureStorage
	{
	private:
		static TextureStorage* g_instance;

		std::map<std::string, sf::Texture> m_texturesMap;
		TextureStorage();
		~TextureStorage();

		void loadTextures();
		void releaseTextures();
	public:

		static void Init();
		static void Destroy();

		static TextureStorage* getInstance();
		sf::Texture & getTexture(std::string name);
	};
}
