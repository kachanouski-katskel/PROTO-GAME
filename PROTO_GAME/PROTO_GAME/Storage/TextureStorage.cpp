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
	m_texturesMap["ground"].loadFromFile("Resources/Textures/ground.png");
	m_texturesMap["water"].loadFromFile("Resources/Textures/water.png");
	m_texturesMap["wall"].loadFromFile("Resources/Textures/Wall.png");
	m_texturesMap["highlight"].loadFromFile("Resources/Textures/highlight.png");
	m_texturesMap["enemy_unit"].loadFromFile("Resources/Textures/enemy_unit.png");
	m_texturesMap["cloud"].loadFromFile("Resources/Textures/cloud3.png");
	m_texturesMap["tower"].loadFromFile("Resources/Textures/tower.png");
	m_texturesMap["ball"].loadFromFile("Resources/Textures/cloud.png");
	m_texturesMap["barracks"].loadFromFile("Resources/Textures/barracks.png");
	m_texturesMap["bastion"].loadFromFile("Resources/Textures/bastion.png");
	m_texturesMap["ice_ball"].loadFromFile("Resources/Textures/ice_ball.png");
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
