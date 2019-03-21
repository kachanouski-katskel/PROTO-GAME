#include "TextureStorage.h"

using namespace ProtoGame;

TextureStorage* TextureStorage::g_instance = nullptr;

TextureStorage::TextureStorage()
{
	loadTextures();
}

TextureStorage::~TextureStorage()
{
}

void ProtoGame::TextureStorage::loadTextures()
{
	sf::Texture texture;
	texture.loadFromFile("Resources/Textures/Wall.png");
	m_texturesMap["wall"] = texture;
}

void ProtoGame::TextureStorage::releaseTextures()
{
}

void TextureStorage::Init()
{
}

void TextureStorage::Destroy()
{

}

TextureStorage* TextureStorage::getInstance()
{
	if (g_instance == nullptr)
	{
		g_instance = new TextureStorage();
	}
	return g_instance;
}

sf::Texture & ProtoGame::TextureStorage::getTexture(std::string name)
{
	return m_texturesMap[name];
}
